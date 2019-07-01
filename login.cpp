#include "login.h"
#include "ui_login.h"

#include <QDebug>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
/*
      @det 		Constructor of the Login class
      @param    void
      @return 	void
*/
{
    ui->setupUi(this);
    design();
}

void Login::design()
/*
    @det 		Method do design the UI
    @param 		void
    @return 	void
*/
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    setFixedSize(700,500);

    setWindowTitle("GENERATOR LOGIN");
    QPixmap loginPic(":img/Encryption.jpg");
    loginPic.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette loginPalette;
    loginPalette.setBrush(QPalette::Background, loginPic);
    setPalette(loginPalette);
    setFont(QFont("Courier", 14, QFont::Bold, true));

    QString forLabels = "font: 20pt; color: #FFFFFFFF";
    username_.setText("Username: ");
    username_.setStyleSheet(forLabels);
    password_.setText("Password: ");
    password_.setStyleSheet(forLabels);
    loginButton_.setText("Login");

    mainLayout->addWidget(&pictureLogin_);
    mainLayout->addWidget(&title_);
    mainLayout->addWidget(&username_);
    mainLayout->addWidget(&usernameInput_);
    mainLayout->addWidget(&password_);
    mainLayout->addWidget(&passwordInput_);
    mainLayout->addWidget(&loginButton_);
    passwordInput_.setEchoMode(QLineEdit::Password);

    // REMOVE AFTER FINISHING
    usernameInput_.setText("Admin");
    passwordInput_.setText("MyPassword");

    QObject::connect(&loginButton_, SIGNAL(clicked()), this, SLOT(authentication()));
    // SET HERE ON PRESSING THE ENTER KEY
    QObject::connect(&loginButton_, SIGNAL(pressed()), this, SLOT(authentication()));
}

void Login::authentication()
/*
    @det 		Slot called when authentication of a user is needed
                    emits a signal of authentication (successfullLogin)
    @param 		void
    @return 	void
*/
{
    if(usernameInput_.text() == "Admin" && passwordInput_.text() == "MyPassword")
    {
        close();
        emit successfullLogin();
    }
    else
    {
        QMessageBox mbox;
        mbox.setText("Invalid Username or Password\n");
        mbox.exec();
    }
}

Login::~Login()
/*
    @det 		Destructor of the Login class
    @param 		void
    @return 	void
*/
{
    delete ui;
}
