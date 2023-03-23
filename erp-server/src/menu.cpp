//! \file menu.cpp
//!
//! \copyright
//!
//! This file is part of the ERPBeyond distribution.
//! Copyright (c) 2023 Joe Turner.
//!
//! This program is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, version 3.
//!
//! This program is distributed in the hope that it will be useful, but
//! WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
//! General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with this program. If not, see <http://www.gnu.org/licenses/>.
#include "menu.h"

MenuWidget::MenuWidget()
{
    // Create a stack where the contents will be located.
    auto contents = std::make_unique<Wt::WStackedWidget>();

    Wt::WMenu *menu = addNew<Wt::WMenu>(contents.get());
    menu->setStyleClass("nav nav-pills flex-column");
    menu->setWidth(150);

    // Add menu items using the default lazy loading policy.
    menu->addItem("Internal paths", std::make_unique<Wt::WTextArea>("Internal paths contents"));
    menu->addItem("Anchor", std::make_unique<Wt::WTextArea>("Anchor contents"));
    menu->addItem("Stacked widget", std::make_unique<Wt::WTextArea>("Stacked widget contents"));
    menu->addItem("Tab widget", std::make_unique<Wt::WTextArea>("Tab widget contents"));
    menu->addItem("Menu", std::make_unique<Wt::WTextArea>("Menu contents"));

    addWidget(std::move(contents));
}
