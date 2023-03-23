//! \file navitagtion.cpp
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
#include "navigation.h"

NavigationBarWidget::NavigationBarWidget()
{
    // Create a navigation bar with a link to a web page.
    Wt::WNavigationBar *navigation = addNew<Wt::WNavigationBar>();
    // It's not necessary to do this with WBootstrap5Theme, but we include it if
    // you want to use another theme.
    navigation->setResponsive(true);
    // WBootstrap5Theme applies no color scheme by default, so we have to add them here.
    navigation->addStyleClass("navbar-light bg-light");
    navigation->setTitle("ERPBeyond");

    Wt::WStackedWidget *contentsStack = addNew<Wt::WStackedWidget>();
    contentsStack->addStyleClass("contents");

    // Setup a Left-aligned menu.
    auto leftMenu = std::make_unique<Wt::WMenu>(contentsStack);
    auto leftMenu_ = navigation->addMenu(std::move(leftMenu));

    auto searchResult = std::make_unique<Wt::WText>("Buy or Sell... Bye!");
    auto searchResult_ = searchResult.get();

    leftMenu_->addItem("Home", std::make_unique<Wt::WText>("There is no better place!"));
    leftMenu_->addItem("Layout", std::make_unique<Wt::WText>("Layout contents"))
        ->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/layout"));
    leftMenu_->addItem("Sales", std::move(searchResult));
    leftMenu_->addStyleClass("me-auto");

#ifdef ENABLE_SEARCH_CONSOLE
    // Add a Search control.
    auto editPtr = std::make_unique<Wt::WLineEdit>();
    auto edit = editPtr.get();
    edit->setPlaceholderText("Enter a search item");

    edit->enterPressed().connect([=]
                                 {
    leftMenu_->select(2); // is the index of the "Sales"
    searchResult_->setText(Wt::WString("Nothing found for {1}.")
                                 .arg(edit->text())); });

    navigation->addSearch(std::move(editPtr));

    // Setup a Right-aligned menu.
    auto rightMenu = std::make_unique<Wt::WMenu>();
    auto rightMenu_ = navigation->addMenu(std::move(rightMenu));

    // Create a popup submenu for the Help menu.
    auto popupPtr = std::make_unique<Wt::WPopupMenu>();
    auto popup = popupPtr.get();
    popup->addItem("Contents");
    popup->addItem("Index");
    popup->addSeparator();
    popup->addItem("About");

    popup->itemSelected().connect([=](Wt::WMenuItem *item)
                                  {
    auto messageBox = popup->addChild(
            std::make_unique<Wt::WMessageBox>
            ("Help",
             Wt::WString("<p>Showing Help: {1}</p>").arg(item->text()),
             Wt::Icon::Information,
             Wt::StandardButton::Ok));

    messageBox->buttonClicked().connect([=] {
        popup->removeChild(messageBox);
    });

    messageBox->show(); });

    auto item = std::make_unique<Wt::WMenuItem>("Help");
    item->setMenu(std::move(popupPtr));
    rightMenu_->addItem(std::move(item));
    #endif 
}