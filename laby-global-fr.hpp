#ifndef LABY_GLOBAL_FR_H
#define LABY_GLOBAL_FR_H

#ifndef ASSERT
#define ASSERT(C) if ( !(C) ) { throw std::runtime_error("\x1b[48;5;224mTest failed: "#C); }
#endif

#include "laby-widget.hpp"

LabySVGViewPlayerApp *app;
auto Caillou     = Tile::Rock;
auto PetitCaillou= Tile::SmallRock;
auto Toile       = Tile::Web;
auto PetiteToile = Tile::SmallWeb;
auto Sortie      = Tile::Exit;
auto Mur         = Tile::Wall;
auto Vide        = Tile::Void;
auto debut()   { return app -> debut();   }
auto avance()  { return app -> avance();  }
auto droite()  { return app -> droite();  }
auto gauche()  { return app -> gauche();  }
auto pose()    { return app -> pose();    }
auto prend()   { return app -> prend();   }
auto ouvre()   { return app -> ouvre();   }
auto regarde() { return app -> regarde(); }
bool a_gagne() { return app -> won();     }

void LABY(std::string s) {
    app = laby_level(s);
}

#endif
