//! \file mainpage.cpp
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
#include "mainpage.h"
#include "application.h"
#include "navigation.h"
#include "menu.h"

MainPage::MainPage()
{
    auto layout = setLayout(std::make_unique<Wt::WBorderLayout>());
    layout->addWidget(std::make_unique<NavigationBarWidget>(), Wt::LayoutPosition::North);
    layout->addWidget(std::make_unique<MenuWidget>(), Wt::LayoutPosition::West);

    // item = std::make_unique<Wt::WText>(Wt::WString(cell).arg("East"));
    // item->setStyleClass("green-box");
    // layout->addWidget(std::move(item), Wt::LayoutPosition::East);

    // item = std::make_unique<Wt::WText>(Wt::WString(cell).arg("South"));
    // item->setStyleClass("green-box");
    // layout->addWidget(std::move(item), Wt::LayoutPosition::South);

    // item = std::make_unique<Wt::WText>(Wt::WString(cell).arg("Center"));
    // item->setStyleClass("green-box");
    // layout->addWidget(std::move(item), Wt::LayoutPosition::Center);
}