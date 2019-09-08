#include "laby.hpp"
using namespace std;

#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl
#define ASSERTEQ(obtained, expected) if (obtained != expected) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ":\nExpected:\n" << expected << "\nGot:\n" << obtained << endl

const string s =
        u8"o o o o o x o\n"
        u8"o . . . . . o\n"
        u8"o . . . . . o\n"
        u8"o . ↑ . . . o\n"
        u8"o o o o o o o\n";

void testLabyrinth() {
    auto l = Labyrinth(s);
    ASSERTEQ( l.to_string(),
        u8"o o o o o x o\n"
        u8"o . . . . . o\n"
        u8"o . . . . . o\n"
        u8"o . ↑ . . . o\n"
        u8"o o o o o o o\n");
    ASSERT( l.avance() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . . . . . o\n"
           u8"o . ↑ . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( l.avance() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . ↑ . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( not l.avance() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . ↑ . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( l.droite() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . → . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( l.droite() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . ↓ . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( l.droite() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . ← . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( l.droite() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . ↑ . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( l.gauche() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . ← . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( l.gauche() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . ↓ . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( l.gauche() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . → . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( l.avance() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . . → . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( l.avance() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . . . → . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( l.avance() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . . . . → o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( l.gauche() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . . . . ↑ o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( not l.avance() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . . . . ↑ o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( l.ouvre() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o ↑ o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( not l.avance() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o ↑ o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
}

void testLabyrinthValueSemantic() {
    auto l = Labyrinth(s);
    auto l2 = l;
    l.avance();
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . . . . . o\n"
           u8"o . ↑ . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERTEQ( l2.to_string(), s);
}

void testLabyApp() {
    auto app = LabyApp(Labyrinth(s));
    ASSERTEQ( app.view.to_string(),
        u8"o o o o o x o\n"
        u8"o . . . . . o\n"
        u8"o . . . . . o\n"
        u8"o . ↑ . . . o\n"
        u8"o o o o o o o\n");
    ASSERTEQ( app.player.time, 0);

    ASSERT( app.avance() );
    ASSERTEQ( app.view.to_string(),
           u8"o o o o o x o\n"
           u8"o . . . . . o\n"
           u8"o . ↑ . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERTEQ( app.player.time, 1);

    ASSERT( app.avance() );
    ASSERTEQ( app.view.to_string(),
           u8"o o o o o x o\n"
           u8"o . ↑ . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERTEQ( app.player.time, 2);

    ASSERT( app.droite() );
    ASSERTEQ( app.view.to_string(),
           u8"o o o o o x o\n"
           u8"o . → . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERTEQ( app.player.time, 3);

    // Check the history
    ASSERTEQ( app.player.history[0].to_string(),
           u8"o o o o o x o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o . ↑ . . . o\n"
           u8"o o o o o o o\n");
    ASSERTEQ( app.player.history[1].to_string(),
           u8"o o o o o x o\n"
           u8"o . . . . . o\n"
           u8"o . ↑ . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERTEQ( app.player.history[2].to_string(),
           u8"o o o o o x o\n"
           u8"o . ↑ . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERTEQ( app.player.history[3].to_string(),
           u8"o o o o o x o\n"
           u8"o . → . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");

    app.player.step_backward();
    ASSERTEQ( app.player.time, 2);
    ASSERTEQ( app.view.to_string(),
           u8"o o o o o x o\n"
           u8"o . ↑ . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( app.droite() );
    ASSERTEQ( app.view.to_string(),
           u8"o o o o o x o\n"
           u8"o . ↑ . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    app.player.step_forward();
    ASSERTEQ( app.view.to_string(),
           u8"o o o o o x o\n"
           u8"o . → . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    app.player.step_forward();
    ASSERTEQ( app.view.to_string(),
           u8"o o o o o x o\n"
           u8"o . ↓ . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
}

void testLoad() {
    auto l = Labyrinth::load(LABY_DATADIR + "/levels/0.laby");
    ASSERTEQ(l.to_string(),
           u8"o o o o o o\n"
           u8"o w . . . x\n"
           u8"o . . . . o\n"
           u8"o . . . . o\n"
           u8"o . ↑ . r o\n"
           u8"o o o o o o\n");
    auto l2 = Labyrinth::load_level("0");
    ASSERTEQ(l.to_string(), l2.to_string());
}

void testHtml() {
    Labyrinth l(s);
    l.pose();
    ASSERTEQ(l.html(), R"html(<table>
    <tr>
        <td><img src='data/tiles/wall.svg'></td>
        <td><img src='data/tiles/wall.svg'></td>
        <td><img src='data/tiles/wall.svg'></td>
        <td><img src='data/tiles/wall.svg'></td>
        <td><img src='data/tiles/wall.svg'></td>
        <td><img src='data/tiles/exit.svg'></td>
        <td><img src='data/tiles/wall.svg'></td>
    </tr>
    <tr>
        <td><img src='data/tiles/wall.svg'></td>
        <td><img src='data/tiles/void.svg'></td>
        <td><img src='data/tiles/void.svg'></td>
        <td><img src='data/tiles/void.svg'></td>
        <td><img src='data/tiles/void.svg'></td>
        <td><img src='data/tiles/void.svg'></td>
        <td><img src='data/tiles/wall.svg'></td>
    </tr>
    <tr>
        <td><img src='data/tiles/wall.svg'></td>
        <td><img src='data/tiles/void.svg'></td>
        <td><img src='data/tiles/void.svg'></td>
        <td><img src='data/tiles/void.svg'></td>
        <td><img src='data/tiles/void.svg'></td>
        <td><img src='data/tiles/void.svg'></td>
        <td><img src='data/tiles/wall.svg'></td>
    </tr>
    <tr>
        <td><img src='data/tiles/wall.svg'></td>
        <td><img src='data/tiles/void.svg'></td>
        <td><img src='data/tiles/ant-n.svg'></td>
        <td><img src='data/tiles/void.svg'></td>
        <td><img src='data/tiles/void.svg'></td>
        <td><img src='data/tiles/void.svg'></td>
        <td><img src='data/tiles/wall.svg'></td>
    </tr>
    <tr>
        <td><img src='data/tiles/wall.svg'></td>
        <td><img src='data/tiles/wall.svg'></td>
        <td><img src='data/tiles/wall.svg'></td>
        <td><img src='data/tiles/wall.svg'></td>
        <td><img src='data/tiles/wall.svg'></td>
        <td><img src='data/tiles/wall.svg'></td>
        <td><img src='data/tiles/wall.svg'></td>
    </tr>
</table>
<pre>Je ne peux pas poser.</pre>
)html");
}

void testRun() {
    auto app = LabyApp(Labyrinth(s));
    app.player.play_fps=4;
    app.avance();
    app.avance();
    app.player.run();
    std::this_thread::sleep_for(1s);
    ASSERTEQ(app.player.time, 2);
    app.avance();
    app.avance();
    app.avance();
    std::this_thread::sleep_for(1s);
    ASSERTEQ(app.player.time, 5);
}

void testBaseDir() {
    // This test assumes the test are run in the source directory
    ASSERTEQ(LABY_BASEDIR, "");
    ASSERTEQ(LABY_DATADIR, "data");
    // std::cout << "base directory: " << __basedir__ << std::endl;
    // std::cout << "data directory: " << __datadir__ << std::endl;
}


int main() {
    testLabyrinth();
    testLabyrinthValueSemantic();
    testLabyApp();
    testLoad();
    testHtml();
    //testRun();
    testBaseDir();
}
