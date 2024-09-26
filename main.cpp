#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    window.setFixedSize(400, 300);

    QPushButton buttonAdd("Add", &window);
    buttonAdd.setGeometry(15, 30, 120, 60);

    QPushButton buttonRemove("Remove", &window);
    buttonRemove.setGeometry(15, 120, 120, 60);

    QPushButton buttonEdit("Edit", &window);
    buttonEdit.setGeometry(15, 210, 120, 60);

    QWidget *formWidget = new QWidget(&window);
    formWidget->setGeometry(160, 30, 200, 200);
    formWidget->hide();
//------------------------------------------
    QFormLayout *formLayout = new QFormLayout(formWidget);
    QLineEdit *nameEdit = new QLineEdit;
    QLineEdit *emailEdit = new QLineEdit;
    formLayout->addRow("Name:", nameEdit);
    formLayout->addRow("Email:", emailEdit);

    QObject::connect(&buttonAdd, &QPushButton::clicked, [&]() {
        formWidget->show();
    });

    QObject::connect(emailEdit, &QLineEdit::returnPressed, [&]() {
        QString name = nameEdit->text();
        QString email = emailEdit->text();

        QFile file("userdata.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << "Name: " << name << "\nEmail: " << email << "\n\n";
            file.close();
        }

        nameEdit->clear();
        emailEdit->clear();
        formWidget->hide();
   });


    /////////////////////////////////////////////////////////////////////////


    QObject::connect(&buttonRemove, &QPushButton::clicked, [&]() {
            QString nameToRemove = nameEdit->text();

            if (nameToRemove.isEmpty()) {
                QMessageBox::warning(&window, "Error", "Please enter the name to remove.");
                return;
            }

            QFile file("userdata.txt");
            if (!file.exists()) {
                QMessageBox::warning(&window, "Error", "The file does not exist.");
                return;
            }

            QFile tempFile("temp_userdata.txt");
            if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::warning(&window, "Error", "Could not open temporary file.");
                return;
            }

            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QTextStream out(&tempFile);

                bool userFound = false;
                while (!in.atEnd()) {
                    QString line = in.readLine();

                    if (line.contains("Name: " + nameToRemove)) {
                        in.readLine();
                        in.readLine();
                        userFound = true;
                    } else {
                        out << line << "\n";
                    }
                }

                file.close();
                tempFile.close();

                if (userFound) {
                    file.remove();
                    tempFile.rename("userdata.txt");
                    QMessageBox::information(&window, "Success", "User data removed.");
                } else {
                    tempFile.remove();
                    QMessageBox::information(&window, "Not Found", "User not found.");
                }

                nameEdit->clear();
            }
        });

    window.show();
    return app.exec();
}
