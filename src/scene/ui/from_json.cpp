#include "../../util/font/font.hpp"
#include "../../geas_object/tile/tile.hpp"
#include "../../resourcemanager/resourcemanager.hpp"
#include "ui.hpp"

UI *UI::from_file(const std::string &path)
{
    json j = ResourceManager::singleton().get_json(path);
    return UI::from_json(j);
}

UI *UI::from_json(json j)
{
    auto *ui = new UI();
    std::string background = j["background"];
    [[maybe_unused]] auto *bg = new Tile(ui, 640.0f, background);
    auto font_name = json_get_or_default<std::string>(j, "font_name", "assets/fonts/vict.png");
    auto font_spacing = json_get_or_default<float>(j, "font_spacing", 1.0f);
    auto font_size = json_get_or_default<float>(j, "font_size", 16.0f);
    Font font(font_name);
    font.line_spacing(font_spacing);
    font.scale(font_size/16.0f);

    UIElement *selected_element = nullptr;
    json elements = j["elements"];
    for (const auto &[key, value] : elements.items()) {
        std::string name = key;

        auto elem = new UIElement(ui, name, value, font);
        if (selected_element == nullptr) {
            selected_element = elem;
        }

        ui->elements[name] = elem;

    }

    auto maybe_selection = j.find("initial_selection");
    if (maybe_selection != j.end()) {
        std::string key = *maybe_selection;
        selected_element = ui->elements[key];
    }

    ui->selection_hint = new Tile(ui, font_size, "assets/textures/arrow.png");
    ui->select(selected_element);

    return ui;
}