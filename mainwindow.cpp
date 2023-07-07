#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVector"
#include "QString"

// Общий интерфейс итератора
template <typename T>
class Iterator {
public:
    virtual T getNext() = 0;
    virtual bool hasMore() = 0;
};

// Конкретный класс итератора для вектора
template <typename T>
class VectorIterator : public Iterator<T> {
public:
    VectorIterator(const std::vector<T>& data) : mData(data), mCurrentIndex(0) {}

    T getNext() override {
        return mData[mCurrentIndex++];
    }

    bool hasMore() override {
        return mCurrentIndex < mData.size();
    }

private:
    const std::vector<T>& mData;
    size_t mCurrentIndex;
};

// Класс-контейнер
template <typename T>
class BreakfastMenu{
  public:
    void add(const T& item) {
        mItems.push_back(item);
    }

    Iterator<T>* createIterator() {
        return new VectorIterator<T>(mItems);
    }
  private:
    std::vector<T> mItems;
};

// Класс-контейнер
template <typename T>
class DinnerMenu{
  public:
    void add(const T& item) {
        mItems.push_back(item);
    }

    Iterator<T>* createIterator() {
        return new VectorIterator<T>(mItems);
    }
  private:
    std::vector<T> mItems;
};

// Класс-контейнер
template <typename T>
class LunchMenu{
  public:
    void add(const T& item) {
        mItems.push_back(item);
    }

    Iterator<T>* createIterator() {
        return new VectorIterator<T>(mItems);
    }
  private:
    std::vector<T> mItems;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    BreakfastMenu<QString> BreakfastList;
    DinnerMenu<QString> DinnerList;
    LunchMenu<QString> LunchList;
    BreakfastList.add("Яичница с овощами (150р)");
    BreakfastList.add("Сырники (170р)");
    DinnerList.add("Диетический суп (210р)");
    DinnerList.add("Миска риса (100р)");
    LunchList.add("Салат цезарь (340р)");
    LunchList.add("Окрошка (140р)");

    Iterator<QString>* BreakfastIterator = BreakfastList.createIterator();
    Iterator<QString>* DinnerIterator = DinnerList.createIterator();
    Iterator<QString>* LunchIterator = LunchList.createIterator();

    while (BreakfastIterator->hasMore()) {
        QString item = BreakfastIterator->getNext();
        ui->listWidget->addItem(item);
    }

    while (DinnerIterator->hasMore()) {
        QString item = DinnerIterator->getNext();
        ui->listWidget->addItem(item);
    }

    while (LunchIterator->hasMore()) {
        QString item = LunchIterator->getNext();
        ui->listWidget->addItem(item);
    }

    delete BreakfastIterator;
    delete DinnerIterator;
    delete LunchIterator;
}

