#ifndef LABY_WIDGET_H
#define LABY_WIDGET_H

#include "xwidgets/xhtml.hpp"
#include "xwidgets/xbox.hpp"
#include "xwidgets/xbutton.hpp"
#include "xwidgets/xlabel.hpp"
#include "xwidgets/xslider.hpp"
#include "laby.hpp"

/*
  (anti) pattern: since I don't know yet how to inherit from an
  existing widgets, all views/apps below contain a widget -- stored in
  the widget attribute -- rather than inherit from; so it can be
  extracted back in the places where one needs an actual widget.
*/

class LabyrinthTextView: public LabyrinthView {
    public:
    xw::html widget;
    auto display() {
        return widget.display();
    }
    LabyrinthTextView(Labyrinth labyrinth) : LabyrinthView(labyrinth) {
        update();
    };
    void update() {
        widget.value = std::string("<pre>\n") + value.to_string() + "</pre>\n";
    }
};

class LabyrinthSVGViewMonolith: public LabyrinthView {
    public:
    xw::html widget;
    auto display() {
        return widget.display();
    }
    LabyrinthSVGViewMonolith(Labyrinth labyrinth) : LabyrinthView(labyrinth) {
        update();
    };
    void update() {
        widget.value = value.html();
    }
};

class LabyrinthSVGView: public LabyrinthView {
    public:
    xw::vbox widget;
    std::vector<std::vector<xw::html>> cells;
    Dimension size;
    auto display() {
        return widget.display();
    }
    LabyrinthSVGView(Labyrinth labyrinth) : LabyrinthView(labyrinth) {
        update();
    };
    void update() {
        if ( value.size() != size ) {
            size = value.size();
            // Reconstruct the array of tiles
            widget = xw::vbox();
            cells = std::vector<std::vector<xw::html>>(size.i);
            for (auto &cell_row: cells) {
                xw::hbox row;
                cell_row = std::vector<xw::html>(size.j);
                for (auto &c: cell_row)
                    row.add(c);
                widget.add(std::move(row));
            }
        }
        for (int i=0; i<size.i; i++)
            for (int j=0; j<size.j; j++)
                cells[i][j].value = std::string("<img src='")+filename(value.get(Position(i,j)))+"' width=32 height=32>";
    }
};

class PlayerView {

    public:
    xw::hbox   widget;

    public:
    PlayerView(Player &player) {
        xw::button button_template;
        button_template.layout().width = "initial";

        auto begin = button_template;
        begin.tooltip = "Begin";
        begin.icon = "fast-backward";
        begin.on_click([&player]() { player.pause(); player.begin(); });
        widget.add(std::move(begin));

        auto backward = button_template;
        backward.tooltip = "Play backward";
        backward.icon = "backward";
        backward.on_click([&player]() { player.backward(); });
        widget.add(std::move(backward));

        auto step_backward = button_template;
        step_backward.tooltip = "Step backward";
        step_backward.icon ="step-backward";
        step_backward.on_click([&player]() { player.pause(); player.step_backward(); });
        widget.add(std::move(step_backward));

        auto pause = button_template;
        pause.tooltip = "Pause";
        pause.icon = "pause";
        pause.on_click([&player]() { player.pause(); });
        widget.add(std::move(pause));

        auto step_forward = button_template;
        step_forward.tooltip = "Step forward";
        step_forward.icon = "step-forward";
        step_forward.on_click([&player]() { player.pause(); player.step_forward(); });
        widget.add(std::move(step_forward));

        auto play = button_template;
        play.tooltip = "Play";
        play.icon = "play";
        play.on_click([&player]() { player.play(); });
        widget.add(std::move(play));

        auto end = button_template;
        end.tooltip = "End";
        end.icon = "fast-forward";
        end.on_click([&player]() { player.pause(); player.end(); });
        widget.add(std::move(end));

        // auto frame_label = xw::label();
        // frame_label.value = "frame: ";
        // widget.add(std::move(frame_label));

        // auto frame = xw::label();
        // frame.value = "";
        // widget.add(std::move(frame));

        auto speed_label = xw::label();
        speed_label.value = "Speed: ";
        widget.add(std::move(speed_label));

        auto speed_slider = xw::slider<int>();
        speed_slider.value = 1;
        speed_slider.min   = 0;
        speed_slider.step  = 1;
        speed_slider.max   = 6;
        XOBSERVE(speed_slider, value, [&player](const auto& s) {
                                    int fps = 1;
                                    for (int i=0; i<s.value; i++) {
                                        fps *= 2;
                                    }
                                    player.set_fps(fps);
                                });
        widget.add(std::move(speed_slider));
    }
    auto display() {
        return widget.display();
    }
};
//         self._speed_slider = IntSlider(0,0,10,1)
//         player_controls = HBox([self._begin, self._backward, self._step_backward,
//                                 self._pause,
//                                 self._play, self._step_forward, self._end,
//                                 self._frame_label, self._frame,
//                                 self._speed_label, self._speed_slider])
//         VBox.__init__(self, [view, player_controls])

//         self._model      = PlayerModel(view, self)
//         self._controller = PlayerThread(self._model, self).start()

//     @traitlets.observe("value")
//     def value_changed(self, change):
//         self._model.set_value(change.new)

class LabySVGViewPlayerApp: public LabyBaseApp<LabyrinthSVGView> {
    xw::vbox widget;
    PlayerView controls;
    public:
    LabySVGViewPlayerApp(Labyrinth labyrinth) : LabyBaseApp<LabyrinthSVGView>(labyrinth), controls(player) {
        widget = xw::vbox();
        widget.add(view.widget);
        widget.add(controls.widget);
    }
    auto display() {
        //player.run(); // Or should this be already be done in e.g. PlayerView
        return widget.display();
    }
};

auto laby_level(std::string level) {
    auto app = new LabySVGViewPlayerApp(Labyrinth::load_level(level));
    app->player.run();
    app->display();
    return app;
}

#endif
