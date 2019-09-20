#include "laby/laby-widget.hpp"
using namespace std;

//#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl
#define ASSERTEQ(obtained, expected) if (obtained != expected) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ":\nExpected:\n" << expected << "\nGot:\n" << obtained << endl

const string s =
        u8"o o o o o x o\n"
        u8"o . . . . . o\n"
        u8"o . . . . . o\n"
        u8"o . ↑ . . . o\n"
        u8"o o o o o o o\n";

void testLabyrinthWidgetView() {
    LabyrinthTextView l((Labyrinth(s)));
}

void testLabySVGViewPlayerApp() {
    auto app = LabySVGViewPlayerApp(Labyrinth(s));
    app.player.run();
    std::this_thread::sleep_for(2s);
}


int main() {
    testLabyrinthWidgetView();
    testLabySVGViewPlayerApp();
}
