#include <QCoreApplication>
#include <QTranslator>
#include <QDebug>
#include <QFile>

void loadTranslations()
{
    // Checking for translations

    QString langCode(getenv("LANG"));
    if (langCode.isEmpty() || langCode == "C" || !langCode.contains("_"))
        langCode = QLocale::system().name();
    if (langCode.contains('.'))
        langCode = langCode.mid(0, langCode.lastIndexOf('.'));

    // Uncomment for testing purposes
    //langCode = "hu_HU";

    qDebug() << "Puzzle Master's current language code is" << langCode;

    if (QFile::exists(":/translations/puzzle-master_" + langCode + ".qm"))
    {
        qDebug() << "A translation for the language code" << langCode << "exists, loading it";
        QTranslator *translator = new QTranslator(QCoreApplication::instance());
        translator->load("puzzle-master_" + langCode, ":/translations");
        QCoreApplication::installTranslator(translator);
    }
    else
    {
        qDebug() << "There is NO translation for the language code" << langCode;
    }
}
