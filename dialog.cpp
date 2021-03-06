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
}

Dialog::~Dialog() {
  delete board;
  delete horizontalGroupBox;
  delete villageGroupBox;
  delete labels;
  delete[] buttons[2];
  delete[] lineEdits[2];

  delete[] exitAction;

  delete thread;
  delete worker;
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
  lineEdits[0]->setText("50");
  layout->addWidget(lineEdits[0]);

  lineEdits[1] = new QLineEdit;
  lineEdits[1]->setText("50");
  layout->addWidget(lineEdits[1]);

  thread = new QThread;
  worker = new Worker(board, 1000000000);
  worker->moveToThread(thread);

  connect(thread, SIGNAL(started()), worker, SLOT(process()));
  connect(worker, SIGNAL(repaint()), this, SLOT(repaint()));
  connect(worker, SIGNAL(finished()), this, SLOT(finished()));
  connect(this, SIGNAL(setBoard(Board*)), worker, SLOT(setBoard(Board*)));

  buttons[0] = new QPushButton("Start");
  QObject::connect(buttons[0], &QPushButton::clicked,
                   [this] { handleStartButton(); });
  layout->addWidget(buttons[0]);

  buttons[1] = new QPushButton("Stop");
  QObject::connect(buttons[1], &QPushButton::clicked,
                   [this] { handleStopButton(); });
  layout->addWidget(buttons[1]);
  buttons[1]->setEnabled(false);

  horizontalGroupBox->setLayout(layout);
  horizontalGroupBox->setFixedHeight(58);
}

void Dialog::createVillageArea() {
  villageGroupBox = new QGroupBox("Dorf");
  villageGroupBox->setMinimumHeight(600);
  villageGroupBox->setMinimumWidth(600);
}

void Dialog::handleStartButton() {
  int x = lineEdits[0]->text().toInt();
  int y = lineEdits[1]->text().toInt();

  board->reset(x, y, 25, 25, 25, 25, 0);

  thread->start();
  buttons[0]->setEnabled(false);
  buttons[1]->setEnabled(true);
}

void Dialog::handleStopButton() {
  thread->requestInterruption();
  thread->quit();
  buttons[0]->setEnabled(true);
  buttons[1]->setEnabled(false);
}

void Dialog::finished() {
  std::cout << "finished" << std::endl;
  handleStopButton();
}

void Dialog::repaint() {
  update();
}

void Dialog::paintEvent(QPaintEvent*) {
  int x = 20;
  int y = 90;
  double oneWidth = (size().width() - 2 * x) / (double)board->getXDim();
  double oneHeight = (size().height() - y - 20) / (double)board->getYDim();
  QPainter painter(this);
  Citizen* citizens = board->getCitizens();
  for (int i = 0; i < board->getYDim(); i++) {
    for (int j = 0; j < board->getXDim(); j++) {
      Citizen citizen = citizens[i * board->getXDim() + j];
      QRect rect =
          QRect((j * oneWidth) + x, (i * oneHeight) + y, oneWidth, oneHeight);
      painter.setPen(QPen(Qt::gray, 2));
      painter.drawRect(rect);
      if (citizen.getParty() == 0) {
        painter.fillRect(rect, Qt::red);
      } else if (citizen.getParty() == 1) {
        painter.fillRect(rect, Qt::cyan);
      } else if (citizen.getParty() == 2) {
        painter.fillRect(rect, Qt::yellow);
      } else {
        painter.fillRect(rect, Qt::green);
      }
    }
  }
}
