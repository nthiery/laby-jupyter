#ifndef LABY_H
#define LABY_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "timer.hpp"

const std::string LABY_FILE = __FILE__;
const std::string LABY_BASENAME = "include/laby/laby.hpp";
const std::string LABY_PREFIX   = LABY_FILE.substr(0, LABY_FILE.length()- LABY_BASENAME.length());
const std::string LABY_SHAREDIR = LABY_PREFIX+"share/laby/";
const std::string LABY_TILEDIR  = LABY_SHAREDIR+"tiles/";
const std::string LABY_LEVELDIR = LABY_SHAREDIR+"levels/";
bool use_inline_svg=true;
std::vector<std::string> svg_images;

std::string utf8_substr(const std::string& str, unsigned int start, size_t leng)
{
    if (leng==0) { return ""; }
    size_t c, i, ix, q;
    unsigned long min=std::string::npos, max=std::string::npos;
    for (q=0, i=0, ix=str.length(); i < ix; i++, q++)
    {
        if (q==start){ min=i; }
        if (q<=start+leng || leng==std::string::npos){ max=i; }

        c = (unsigned char) str[i];
        if      (
                 //c>=0   &&
                 c<=127) i+=0;
        else if ((c & 0xE0) == 0xC0) i+=1;
        else if ((c & 0xF0) == 0xE0) i+=2;
        else if ((c & 0xF8) == 0xF0) i+=3;
        //else if (($c & 0xFC) == 0xF8) i+=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
        //else if (($c & 0xFE) == 0xFC) i+=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
        else return "";//invalid utf8
    }
    if (q<=start+leng || leng==std::string::npos){ max=i; }
    if (min==std::string::npos || max==std::string::npos) { return ""; }
    return str.substr(min,max-min);
}

unsigned char utf8_len(const std::string& str)
{
    unsigned int l=0;
    unsigned int c;
    for ( unsigned int i=0; i < str.length(); i++, l++ )
    {
        c = (unsigned char) str[i];
        if      (
                 c<=127) i+=0;
        else if ((c & 0xE0) == 0xC0) i+=1;
        else if ((c & 0xF0) == 0xE0) i+=2;
        else if ((c & 0xF8) == 0xF0) i+=3;
        else throw std::runtime_error("invalid utf8");
    }
    return l;
}

struct Position {
    int i;
    int j;
    public:
    Position(): i(0), j(0) {};
    Position(int _i, int _j): i(_i), j(_j) {};
    bool operator ==(Position pos2) {
        return ( i == pos2.i ) and ( j == pos2.j );
    };
    bool operator !=(Position pos2) {
        return ! ( *this == pos2 );
    };
};
std::ostream& operator<<(std::ostream& os, const Position& pos)
{
    os << "(" << pos.i << ", " << pos.j << ")";
    return os;
}

using Dimension = Position;

enum class Direction { North, West, South, East };
std::vector<Position> directions = { {-1,0}, {0,-1}, {1,0}, {0,1} };

enum Tile {
    AntE, AntN, AntS, AntW, Exit, SmallRock, SmallWeb, Rock, Void, Wall, Web, Outside, RandomRock, RandomWeb
};

// Assumption: fake tiles are rendered as void
std::vector<std::string> tilenames = {
    "ant-e", "ant-n", "ant-s", "ant-w", "exit", "nrock", "nweb", "rock", "void", "wall", "web", "void", "void", "void"
};
std::vector<std::string> tilechars = {
    u8"→", u8"↑", u8"↓", u8"←", "x", "ŕ", "ẃ", "r", ".", "o", "w", " ", "R", "W"
    
};

enum PlayDirection { Forward, Backward, None };

std::vector<Tile> ant_tiles = { AntN, AntW, AntS, AntE };

Tile char_to_tile(std::string c) {
    for ( unsigned int i=0; i < tilechars.size(); i++ ) {
        if ( c == tilechars[i] ) {
            return Tile(i);
        }
    }
    throw std::runtime_error("no tile found");
}

std::string read_file(std::string filename) {
    std::ifstream t(filename);
    if ( not t )
        throw std::runtime_error(std::string("file not found: ")+filename);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

std::string filename(Tile tile) {
    return "/nbextensions/laby/"+tilenames[tile]+".svg";
}

std::string svg_image(Tile tile) {
    if ( use_inline_svg ) {
        if ( svg_images.size() == 0 ) {
            for ( auto tilename: tilenames ) {
                std::string temp = read_file(LABY_TILEDIR + tilename + ".svg");
                svg_images.push_back(temp);
            }
        }
        return svg_images[tile];        
    }
    return "<img src='"+filename(tile)+"' width=32 height=32>";
}

class Board : public std::vector<std::vector<Tile>> {
    public:
    Tile get(Position position) {
        if (position.i < 0 or
            position.j < 0 or
            position.i >= size() or
            position.j >= at(0).size()) {
            return Tile::Outside;
        }
        return at(position.i)[position.j];
    }
    void set(Position position, Tile tile) {
        if (position.i < 0 or
            position.j < 0 or
            position.i >= size() or
            position.j >= at(0).size()) {
            // TODO: use a more precise exception
            throw std::runtime_error("position out of the board");
        }
        at(position.i)[position.j] = tile;
    }
};

class Labyrinth {
    Board board;
    Position position;
    Direction direction = Direction::North;
    Tile carry = Void;
    std::string message;
    bool _won = false;
    public:

    //////////////////////////////////////////////////////////////////////////
    // Constructors
    Labyrinth() {
    }

    Labyrinth(std::string s) {
        from_string(s);
    }

    static
    Labyrinth load_level(std::string level) {
        // TODO: Should use the analogue of os.path
        return load(LABY_LEVELDIR+"/"+level+".laby");
    }

    static
    Labyrinth load(std::string file) {
        std::ifstream fd;
        fd.open(file);
        if ( not fd )
            throw std::runtime_error(std::string("file not found: ")+file);
        std::string line;
        std::string s;
        getline(fd, line);
        getline(fd, line);
        while ( line.size() > 0 ) {
            s += line + "\n";
            getline(fd, line);
        }
        fd.close();
        Labyrinth l;
        l.from_string(s);
        return l;
    }

    void from_string(std::string s) {
        board = Board();
        std::stringstream fd(s);
        std::string l;
        int i = 0;
        while ( getline(fd, l) ) {
            std::vector<Tile> line;
            for (int j = 0; 2*j < utf8_len(l); j++) {
                Tile tile = char_to_tile(utf8_substr(l, 2*j,1));
                for (unsigned int dir = 0; dir < 4; dir ++) {
                    if ( tile == ant_tiles[dir] ) {
                        position = { i, j };
                        direction = Direction(dir);
                        tile = Tile::Void;
                        break;
                    }
                }
                line.push_back(tile);
            }
            board.push_back(line);
            i++;
        }
    }

    std::string to_string() {
        std::string s = "";
        for ( auto line: view() ) {
            for (int j=0; j<line.size(); j++ ) {
                s += tilechars[line[j]];
                if ( j < line.size() - 1 )
                    s+= " ";
            }
            s += "\n";
        }
        return s;
    }    

    std::vector<Tile> tiles_at_position(Position p) {
        std::vector<Tile> res = {};                                         
        Tile tile = board.get(p);
        res.push_back(tile);                    
        if( p == position){                
           res.push_back(ant_tiles[int(direction)]);
           if(carry != Tile::Void){
                res.push_back(carry);
           }
        }                            
        return res;
    }
    
    std::string tiles_to_html(std::vector<Tile> tiles)  {       
        std::string s = "";
        std::string temp = "";        
        for(int i=tiles.size()-1; i>=0; i--) {                    
            if(i > 0){                
                s = "<div style='position: relative;'> " + svg_image(tiles[i]) + " </div>" + s;
                int index = s.find("height=");                
                s.insert(index, " class='tile' ");
            }
            else{
                s += svg_image(tiles[i]);
            }
        }
        s = " <td>" + s;
        s += "</td>\n";
        return s;
    }
    
    std::string html(){          
        std::string s = "<style> .tile { position: absolute;  } </style>\n";
        s += "<table style='line-height: 0pt;'>\n";
        for(int i = 0 ; i < board.size() ; i++) {
            s += "    <tr>\n";
            for(int j = 0 ; j < board[i].size() ; j++) {
                s += "       " + tiles_to_html(tiles_at_position(Position(i,j)));
            }
            s += "    </tr>\n";
        }
        s+="</table>\n";
        s+="<pre>";
        if ( message.empty() )
            s += " ";
        s += message;
        s += "</pre>\n";
        return s;
    }

    Board view() {
        Board view = board;
        if ( position.i < view.size() and
             position.j < view[position.i].size())
            // The ant is on the board; display it
            view[position.i][position.j] = ant_tiles[int(direction)];
        return view;
    }

    Tile get(Position pos) {
        if (pos == position)
            return ant_tiles[int(direction)];
        else
            return board.get(pos);
    }

    Dimension size() {
        Dimension size;
        size.i = board.size();
        size.j = size.i == 0 ? 0 : board[0].size();
        return size;
    }

    void randomize() {
        int n_random_rocks = 0;
        int n_random_webs = 0;
        for (auto row: board) {
            for (auto c: row) {
                if (c == RandomRock)
                    n_random_rocks ++;
                if (c == RandomWeb)
                    n_random_webs ++;
            }
        }
        int r_rock = n_random_rocks ? rand() % n_random_rocks : 0;
        int r_web  = n_random_webs  ? rand() % n_random_webs  : 0;
        n_random_rocks = 0;
        n_random_webs = 0;
        for (auto &row: board) {
            for (auto &c: row) {
                if (c == RandomRock) {
                    if (n_random_rocks == r_rock)
                        c = SmallRock;
                    else
                        c = Rock;
                    n_random_rocks ++;
                }
                if (c == RandomWeb) {
                    if (n_random_webs == r_web)
                        c = SmallWeb;
                    else
                        c = Web;
                    n_random_webs ++;
                }
            }
        }
    }

    void win() {
        _won = true;
        message = "J'ai gagné!";
    }
    bool won() {
        return _won;
    }

    Position devant() {
        Position diff = directions[int(direction)];
        return Position({position.i+diff.i, position.j+diff.j});
    }

    bool gauche() {
        switch (direction) {
        case Direction::North: direction=Direction::West;  break;
        case Direction::East:  direction=Direction::North; break;
        case Direction::South: direction=Direction::East;  break;
        case Direction::West:  direction=Direction::South; break;
        }
        message = "";
        return true;
    }

    bool droite() {
        switch (direction) {
        case Direction::North: direction=Direction::East;  break;
        case Direction::East:  direction=Direction::South; break;
        case Direction::South: direction=Direction::West;  break;
        case Direction::West:  direction=Direction::North; break;
        }
        message = "";
        return true;
    }

    bool avance() {
        Tile tile = board.get(position);
        Tile tile_devant = board.get(devant());
        if ( tile == Tile::Web or
             tile == Tile::Exit or
             tile_devant == Tile::Outside or
             tile_devant == Tile::Rock or
             tile_devant == Tile::Exit or
             tile_devant == Tile::Wall) {
            message = "Je ne peux pas avancer.";
            return false;
        }
        message = "";
        position = devant();
        return true;
    }

    Tile regarde() {
        Tile tile = board.get(devant());
        message = "";
        return tile;
    }

    bool prend() {
        if ( carry == Tile::Void and regarde() == Tile::Rock ) {
            carry = Tile::Rock;
            board.set(devant(), Tile::Void);
            message = "";
            return true;
        }
        message = "Je ne peux pas prendre.";
        return false;
    }

    bool pose() {
        if ( carry == Tile::Rock and
             (regarde() == Tile::Void or
              regarde() == Tile::Web or
              regarde() == Tile::SmallWeb or
              regarde() == Tile::SmallRock)) {
            carry = Tile::Void;
            board.set(devant(), Tile::Rock);
            message = "";
            return true;
        }
        message = "Je ne peux pas poser.";
        return false;
    }

    bool sow() {
        Tile tile = board.get(position);
        if ( tile == Tile::Web or
             tile == Tile::Exit ) {
            message = "Je ne peux pas semer.";
            return false;
        }
        board.set(position, Tile::SmallRock);
        return true;
    }

    bool ouvre() {
        if ( regarde() != Tile::Exit ) {
            message = "Je ne peux pas ouvrir.";
            return false;
        }
        if ( carry != Tile::Void ) {
            message = "Je ne peux pas ouvrir en portant un objet.";
            return false;
        }
        position = devant();
        win();
        return true;
    }
};

class LabyrinthView {
    public:
    Labyrinth value;

    LabyrinthView(Labyrinth labyrinth) {
        value = labyrinth;
    }
    std::string to_string() {
        return value.to_string();
    }
    virtual void update() {
    }
};


// TODO
// add lock to garantee that no two threads touch the time and history
// at the same time.

class Player {
    LabyrinthView &view;
    public: // for debuging
    Labyrinth original_value;
    std::vector<Labyrinth> history;
    int time;

    // The direction and number of frames per second, when playing
    PlayDirection play_direction;
    int play_fps;
    Timer timer;

    // A player can be used in two modes
    // - With a timer; then the player controls when new values
    //   are displayed
    // - Without a timer; new values are immediately displayed
    //   when at the end of history
    //   Use case: testing
    // The player starts by default without timer; calling run
    // launches the timer

    public:
    Player(LabyrinthView &_view):
        view(_view),
        original_value(view.value),
        play_direction(PlayDirection::Forward),
        play_fps(1),
        timer(std::bind(&Player::tick, this), play_fps) {
        reset();
    }

    void run() {
        timer.run();
    }

    void update() {
        view.value = history[time];
        view.update();
    }

    // TODO: find better names
    Labyrinth get_value() {
        return history[history.size()-1];
    }

    void set_value(Labyrinth value) {
        if ( history.size() > 10000 )
            throw std::runtime_error("Votre programme a pris plus de 1000 étapes");
        history.push_back(value);
        if (not timer.running() and time == history.size() - 2 ) {
            time++;
            update();
        }
    }

    void tick() {
        if (play_direction == Forward)
            step_forward();
        else
            step_backward();
    }

    void reset() {
        time = 0;
        auto randomized = original_value;
        randomized.randomize();
        history = std::vector<Labyrinth>({randomized});
        update();
    }

    void begin() {
        time = 0;
        update();
    }

    void end() {
        time = history.size() - 1;
        update();
    }

    void step_backward() {
        if ( time > 0 ) {
            time--;
            update();
        }
    }
    void step_forward() {
        if ( time < history.size() - 1 ) {
            time++;
            update();
        }
    }

    void backward() {
        play_direction = PlayDirection::Backward;
        timer.set_fps(play_fps);
    }

    void play() {
        play_direction = PlayDirection::Forward;
        timer.set_fps(play_fps);
    }

    void pause() {
        play_direction = PlayDirection::None;
        timer.set_fps(0);
    }

    void set_fps(int fps) {
        play_fps = fps;
        if (play_direction != PlayDirection::None)
            timer.set_fps(fps);
    }

    bool won() {
        return history[history.size()-1].won();
    }
};

template <class LabyrinthView>
class LabyBaseApp {
    public:
    LabyrinthView view;
    Player player;
    LabyBaseApp(Labyrinth labyrinth) : view(labyrinth), player(view) {
    }

    auto debut() {
        player.reset();
    }

    auto avance() {
        auto value = player.get_value();
        auto res = value.avance();
        player.set_value(value);
        return res;
    }
    auto droite() {
        auto value = player.get_value();
        auto res = value.droite();
        player.set_value(value);
        return res;
    }
    auto gauche() {
        auto value = player.get_value();
        auto res = value.gauche();
        player.set_value(value);
        return res;
    }
    auto prend() {
        auto value = player.get_value();
        auto res = value.prend();
        player.set_value(value);
        return res;
    }
    
    auto pose() {
        auto value = player.get_value();
        auto res = value.pose();
        player.set_value(value);
        return res;
    }
    
    auto sow() {
        auto value = player.get_value();
        auto res = value.sow();
        player.set_value(value);
        return res;
    }
    
    auto regarde() {
        return player.get_value().regarde();
    }
    auto ouvre() {
        auto value = player.get_value();
        auto res = value.ouvre();
        player.set_value(value);
        return res;
    }
    bool won() {
        return player.won();
    }
};

using LabyApp = LabyBaseApp<LabyrinthView>;

#endif
