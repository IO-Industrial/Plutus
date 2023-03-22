//! \brief Web application program entry point
//! \file main.cpp
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
#include <Wt/WApplication.h>
#include <Wt/WBootstrap2Theme.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WServer.h>

#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>

#include "session.h"

class AuthApplication : public Wt::WApplication
{
public:
  AuthApplication(const Wt::WEnvironment& env)
    : WApplication(env),
      session_(appRoot() + "auth.db")
  {
    session_.login().changed().connect(this, &AuthApplication::authEvent);

    root()->addStyleClass("container");
    setTheme(std::make_shared<Wt::WBootstrap2Theme>());

    useStyleSheet("css/style.css");

    std::unique_ptr<Wt::Auth::AuthWidget> authWidget
        = std::make_unique<Wt::Auth::AuthWidget>(Session::auth(), session_.users(), session_.login());

    authWidget->model()->addPasswordAuth(&Session::passwordAuth());
    authWidget->model()->addOAuth(Session::oAuth());
    authWidget->setRegistrationEnabled(true);

    authWidget->processEnvironment();

    root()->addWidget(std::move(authWidget));
  }

  void authEvent() {
    if (session_.login().loggedIn()) {
      const Wt::Auth::User& u = session_.login().user();
      log("notice")
        << "User " << u.id()
        << " (" << u.identity(Wt::Auth::Identity::LoginName) << ")"
        << " logged in.";
    } else
      log("notice") << "User logged out.";
  }

private:
  Session session_;
};

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env)
{
  return std::make_unique<AuthApplication>(env);
}

int main(int argc, char **argv)
{
  try {
    Wt::WServer server{argc, argv, WTHTTP_CONFIGURATION};

    server.addEntryPoint(Wt::EntryPointType::Application, createApplication);

    Session::configureAuth();

    server.run();
  } catch (Wt::WServer::Exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (Wt::Dbo::Exception &e) {
    std::cerr << "Dbo exception: " << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }
}