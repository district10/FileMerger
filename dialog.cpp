#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("File Merger"));
    initMem(&m);
}

Dialog::~Dialog()
{
    delete ui;
    freeMem(&m);
}

void Dialog::on_pushButton_selectfiles_clicked()
{
    QStringList names = QFileDialog::getOpenFileNames(this,
                                                      "Select one or more files to open",
                                                      "E:/QtPro",
                                                      "Images (*.png *.raw *.jpg *.txt *.*)");
    qDebug() << names;
    foreach (const QString &str, names) {
        qDebug() << "reading " << str << ": ";
        FILE *fp = fopen(str.toStdString().c_str(), "rb");

        fseek(fp, 0, SEEK_END);
        size_t filesz = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        char *b = (char *)malloc(filesz);
        fread(b, 1, filesz, fp);
        patchMem(&m, filesz, b);

        qDebug() << "filesz: " << filesz;

        fclose(fp);
    }
}

void Dialog::on_pushButton_save_clicked()
{
    saveMem("out.bin", &m);
}

void Dialog::on_pushButton_trans_clicked()
{
    QString name = QFileDialog::getOpenFileName(this,
                                                      "Select one file to open",
                                                      "E:/BCD",
                                                      "Images (*.png *.raw *.jpg *.txt *.bin)");
    loadParseSave(name.toStdString().c_str(), "out.txt");
}
