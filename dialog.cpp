#include <dialog.h>

Dialog::Dialog() {
  board = new Board(50, 50, 25, 25, 25, 25, 0);
  createHorizontalGroupBox();
  createVillageArea();

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addWidget(horizontalGroupBox);
  mainLayout->addWidget(villageGroupBox);
  setLayout(mainLayout);

  setWindowTitle("Demokratur");
  update();
}

Dialog::~Dialog() {
  delete board;
  delete horizontalGroupBox;
  delete villageGroupBox;
  delete labels;
  delete[] buttons[2];
  delete[] lineEdits[2];

  delete[] exitAction;
}

void Dialog::setLabels(QLabel* pLabels) {
  labels = pLabels;
}

QLabel* Dialog::getLabels() {
  return labels;
}

void Dialog::createHorizontalGroupBox() {
  horizontalGroupBox = new QGroupBox("Eingabe:");
  QHBoxLayout* layout = new QHBoxLayout;

  lineEdits[0] = new QLineEdit;
  lineEdits[0]->setText("10");
  layout->addWidget(lineEdits[0]);

  lineEdits[1] = new QLineEdit;
  lineEdits[1]->setText("10");
  layout->addWidget(lineEdits[1]);

  QObject::connect(this, SIGNAL(triggerStart(int)), board,
                   SLOT(triggerStart(int)));

  QObject::connect(this, SIGNAL(triggerStop()), board, SLOT(triggerStop()));

  QObject::connect(board, SIGNAL(repaint()), this, SLOT(repaint()));

  QObject::connect(board, SIGNAL(finished()), this, SLOT(finished()));

  buttons[0] = new QPushButton("Start");
  QObject::connect(buttons[0], &QPushButton::clicked, [this] {
    int x = lineEdits[0]->text().toInt();
    int y = lineEdits[1]->text().toInt();
    delete board;
    board = new Board(x, y, 25, 25, 25, 25, 0);

    QThread* thread = new QThread;
    Worker* worker = new Worker(board, 10000000);
    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(worker, SIGNAL(repaint()), this, SLOT(repaint()));
    thread->start();
  });
  layout->addWidget(buttons[0]);

  buttons[1] = new QPushButton("Stop");
  QObject::connect(buttons[1], &QPushButton::clicked,
                   [this] { std::cout << "TODO implement stop"; });
  layout->addWidget(buttons[1]);

  horizontalGroupBox->setLayout(layout);
  horizontalGroupBox->setFixedHeight(58);
}

void Dialog::createVillageArea() {
  villageGroupBox = new QGroupBox("Dorf");
  villageGroupBox->setMinimumHeight(600);
  villageGroupBox->setMinimumWidth(600);
}

void Dialog::finished() {
  // TODO popup oÄ
}

void Dialog::repaint() {
  this->update();
}

void Dialog::paintEvent(QPaintEvent*) {
  int x = 20;
  int y = 90;
  double oneWidth = (size().width() - 2 * x) / (double)board->getXDim();
  double oneHeight = (size().height() - y - 20) / (double)board->getXDim();
  QPainter painter(this);
  // TODO iterate over citizens
  for (int i = 0; i < board->getXDim(); i++) {
    for (int j = 0; j < board->getYDim(); j++) {
      Citizen* citizens = board->getCitizens();
      Citizen citizen = citizens[i * board->getXDim() + j];
      QRect rect =
          QRect((j * oneWidth) + x, (i * oneHeight) + y, oneWidth, oneHeight);
      painter.setPen(QPen(Qt::gray, 2));
      painter.drawRect(rect);
      if (citizen.GetParty() == 0) {
        painter.fillRect(rect, Qt::red);
      } else if (citizen.GetParty() == 1) {
        painter.fillRect(rect, Qt::cyan);
      } else if (citizen.GetParty() == 2) {
        painter.fillRect(rect, Qt::yellow);
      } else {
        painter.fillRect(rect, Qt::green);
      }
    }
  }
}
