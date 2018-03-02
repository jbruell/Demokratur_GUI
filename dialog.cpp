#include <dialog.h>

Dialog::Dialog() {

    createHorizontalGroupBox();
    createVillageArea();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(villageGroupBox);
    setLayout(mainLayout);
    std::cout << size().height() << std::endl;

    setWindowTitle("Demokratur");
    update();

    // TODO implement Observer pattern
    //*******************
    // https://sourcemaking.com/design_patterns/observer/cpp/3
    //*******************
}

Dialog::~Dialog() {
    delete board;
    delete horizontalGroupBox;
    delete villageGroupBox;
    delete[] buttons[2];
    delete[] lineEdits[2];

    delete[] exitAction;
}

void Dialog::setLabels(QLabel *pLabels) {
    labels = pLabels;
}

QLabel* Dialog::getLabels() {
    return labels;
}

void Dialog::createHorizontalGroupBox() {
    horizontalGroupBox = new QGroupBox("Eingabe:");
    QHBoxLayout *layout = new QHBoxLayout;

    lineEdits[0] = new QLineEdit;
    lineEdits[0]->setText("10");
    layout->addWidget(lineEdits[0]);

    lineEdits[1] = new QLineEdit;
    lineEdits[1]->setText("10");
    layout->addWidget(lineEdits[1]);

    buttons[0] = new QPushButton("Start");
    QObject::connect(buttons[0], &QPushButton::clicked, [this]{
        int x = lineEdits[0]->text().toInt();
        int y = lineEdits[1]->text().toInt();
        board = new Board(x, y, 25, 25 ,25, 25, 0);
        board->start(1000000);
    });
    // TODO Button connect, create board
    layout->addWidget(buttons[0]);

    buttons[1] = new QPushButton("Stop");
    QObject::connect(buttons[1], &QPushButton::clicked, [this]{
        std::cout <<"test";
    });
    layout->addWidget(buttons[1]);

    horizontalGroupBox->setLayout(layout);
}

void Dialog::createVillageArea() {
    villageGroupBox = new QGroupBox("Dorf");
    villageGroupBox->setFixedHeight(600);
    villageGroupBox->setFixedWidth(600);
}

void Dialog::paintEvent(QPaintEvent *) {
    if (board != NULL) {
    int x = 20;
    int y = 90;
    int oneWidth = (size().width() - 2 * x) / 50;
    int oneHeight = (size().height() - y - 20) / 50;
    QPainter painter(this);
    // TODO iterate over citizens
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            QRect rect = QRect(j * oneWidth + x, i * oneHeight + y, oneWidth, oneHeight);
            painter.setPen(QPen(Qt::gray, 2));
            painter.drawRect(rect);
            painter.fillRect(rect, Qt::red);
        }
    }
}
}
