#include "laby/laby.hpp"
using namespace std;

#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl
#define ASSERTEQ(obtained, expected) if (obtained != expected) cout << __FILE__ << ":" << __LINE__ << ": Test failed:\nExpected:\n" << expected << "\nGot:\n" << obtained << endl

const string s =
        u8"o o o o o x o\n"
        u8"o . . . . . o\n"
        u8"o . . . . . o\n"
        u8"o . ↑ . . . o\n"
        u8"o o o o o o o\n";   

void testSvgImage() {
    svg_image(Tile::Exit);
}

void testFilename() {
    ASSERTEQ(filename(Tile::Wall), "/nbextensions/laby/wall.svg");
}

void testLabyrinth() {
    auto l = Labyrinth(s);
    ASSERTEQ( l.to_string(),
        u8"o o o o o x o\n"
        u8"o . . . . . o\n"
        u8"o . . . . . o\n"
        u8"o . ↑ . . . o\n"
        u8"o o o o o o o\n");
    ASSERT( not l.won() );
    ASSERT( l.avance() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o x o\n"
           u8"o . . . . . o\n"
           u8"o . ↑ . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");
    ASSERT( not l.won() );
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
    ASSERT( l.won() );
    ASSERT( not l.avance() );
    ASSERTEQ( l.to_string(),
           u8"o o o o o ↑ o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o . . . . . o\n"
           u8"o o o o o o o\n");

}

 

void testStack(){
    // Rendre le labyrinth minimal.
    const string stack_test= u8"o . → r . x";
    
    auto l_stack = Labyrinth(stack_test);
    ASSERTEQ( l_stack.to_string(),
        u8"o . → r . x");
    ASSERTEQ(l.html(), R"html(<table style='line-height: 0pt;'>
    <tr>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/ant-e.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/rock.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/exit.svg' width=32 height=32></td>
    </tr>
</table>
<pre> </pre>
)html");
    ASSERT(not l.avance());
    ASSERT( l.prend());
    ASSERTEQ(l.html(), R"html(<table style='line-height: 0pt;'>
    <tr>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><div style='position: relative; left: 5px; top: 5px;'> <img id='rock_carry' src='rock.svg' width=20 height=20 class='stack' > </div>
            <img src='/nbextensions/laby/ant-e.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/exit.svg' width=32 height=32></td>
    </tr>
</table>
<pre></pre>
)html");
    ASSERT( l.avance());
    ASSERTEQ(l.html(), R"html(<table style='line-height: 0pt;'>
    <tr>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><div style='position: relative; left: 5px; top: 5px;'> <img id='rock_carry' src='rock.svg' width=20 height=20 class='stack' > </div>
            <img src='/nbextensions/laby/ant-e.svg' width=32 height=32></td>        
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/exit.svg' width=32 height=32></td>
    </tr>
</table>
<pre></pre>
)html");
    ASSERT( l.avance());
    ASSERTEQ(l.html(), R"html(<table style='line-height: 0pt;'>
    <tr>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><div style='position: relative; left: 5px; top: 5px;'> <img id='rock_carry' src='rock.svg' width=20 height=20 class='stack' > </div>
            <img src='/nbextensions/laby/ant-e.svg' width=32 height=32></td>                
        <td><img src='/nbextensions/laby/exit.svg' width=32 height=32></td>
    </tr>
</table>
<pre></pre>
)html");
    ASSERT( l.gauche());
    ASSERTEQ(l.html(), R"html(<table style='line-height: 0pt;'>
    <tr>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><div style='position: relative; left: 5px; top: 5px;'> <img id='rock_carry' src='rock.svg' width=20 height=20 class='stack' > </div>
            <img src='/nbextensions/laby/ant-e.svg' width=32 height=32></td>                
        <td><img src='/nbextensions/laby/exit.svg' width=32 height=32></td>
    </tr>
</table>
<pre></pre>
)html");
    ASSERT( l.gauche());
    ASSERTEQ(l.html(), R"html(<table style='line-height: 0pt;'>
    <tr>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><div style='position: relative; left: 5px; top: 5px;'> <img id='rock_carry' src='rock.svg' width=20 height=20 class='stack' > </div>
            <img src='/nbextensions/laby/ant-e.svg' width=32 height=32></td>                
        <td><img src='/nbextensions/laby/exit.svg' width=32 height=32></td>
    </tr>
</table>
<pre></pre>
)html");
    ASSERT( l.pose());
    ASSERTEQ(l.html(), R"html(<table style='line-height: 0pt;'>
    <tr>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/rock.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/ant-e.svg' width=32 height=32></td>                
        <td><img src='/nbextensions/laby/exit.svg' width=32 height=32></td>
    </tr>
</table>
<pre></pre>
)html");
    ASSERT( l.gauche());
    ASSERTEQ(l.html(), R"html(<table style='line-height: 0pt;'>
    <tr>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/rock.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/ant-e.svg' width=32 height=32></td>                
        <td><img src='/nbextensions/laby/exit.svg' width=32 height=32></td>
    </tr>
</table>
<pre></pre>
)html");
    ASSERT( l.gauche());
    ASSERTEQ(l.html(), R"html(<table style='line-height: 0pt;'>
    <tr>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/rock.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/ant-e.svg' width=32 height=32></td>                
        <td><img src='/nbextensions/laby/exit.svg' width=32 height=32></td>
    </tr>
</table>
<pre></pre>
)html");
    ASSERT( l.ouvre());    
}

void testSow() {
    auto l = Labyrinth(". → w . ");
    ASSERT( l.sow() );
    l.avance();
    ASSERTEQ( l.to_string(), u8". ŕ → .\n" );
    ASSERT( not l.sow() );

    l = Labyrinth("→ x");
    ASSERT( l.ouvre() );
    ASSERTEQ( l.to_string(), u8". →\n" );
    ASSERT( not l.sow() );
}

void testSize() {
    auto l = Labyrinth("");
    ASSERTEQ( l.size(), Dimension(0, 0) );
    l = Labyrinth(s);
    ASSERTEQ( l.size(), Dimension(5, 7) );
}

void testViewAt() {
    auto l = Labyrinth(s);
    auto view = l.view();
    auto size = l.size();
    for (int i=-1; i<=size.i; i++) {
        for (int j=-1; j<=size.j; j++) {
            auto pos = Position(i,j);
            ASSERTEQ(l.get(pos), view.get(pos));
        }
    }
    ASSERTEQ(Tile::Outside, view.get(Position(5,0)));
    ASSERTEQ(Tile::Outside, view.get(Position(0,7)));
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
    auto l = Labyrinth::load(LABY_LEVELDIR + "0.laby");
    ASSERTEQ(l.to_string(),
           u8"o o o o o o\n"
           u8"o w . . . x\n"
           u8"o . . . . o\n"
           u8"o . . . . o\n"
           u8"o . ↑ . r o\n"
           u8"o o o o o o\n");
    auto l0 = Labyrinth::load_level("0");
    ASSERTEQ(l.to_string(), l0.to_string());
    auto l3a = Labyrinth::load_level("3a");
    l3a.html(); // Checks that html rendering of non-tiles does not break
}

void testHtml() {
    Labyrinth l(s);
    l.pose();
    use_inline_svg = false;
    ASSERTEQ(l.html(), R"html(<table style='line-height: 0pt;'>
    <tr>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/exit.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
    </tr>
    <tr>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
    </tr>
    <tr>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
    </tr>
    <tr>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/ant-n.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/void.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
    </tr>
    <tr>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
        <td><img src='/nbextensions/laby/wall.svg' width=32 height=32></td>
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
    ASSERTEQ(LABY_PREFIX, "");
    ASSERTEQ(LABY_SHAREDIR, "share/laby/");
    // std::cout << "base directory: " << __basedir__ << std::endl;
    // std::cout << "data directory: " << __datadir__ << std::endl;
}

void testRandomize() {
    Labyrinth("W").html();
    Labyrinth l = Labyrinth::load_level("3a");
    l.html();
    Labyrinth c = l; c.randomize();
    c = l; c.randomize();
    c = l; c.randomize();
}

void testRandomizedPlayer() {
    auto app  = LabyApp(Labyrinth::load_level("3a"));
    auto app2 = LabyApp(Labyrinth::load_level("3b"));
}

int main() {
    testSvgImage();
    testFilename();
    testViewAt();
    testLabyrinth();
    testStack();
    testSow();
    testLabyrinthValueSemantic();
    testLabyApp();
    testLoad();
    testHtml();
    //testRun();
    testBaseDir();
    testRandomize();
    testRandomizedPlayer();
}
