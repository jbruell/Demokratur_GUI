#include <dialog.h>

// public methods

Dialog::Dialog() {
  board = new Board(15, 15, 50);
  reset = false;
  createHorizontalGroupBox();
  createVillageArea();

  QVBoxLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(horizontalGroupBox);
  mainLayout->addWidget(villageGroupBox);
  setLayout(mainLayout);

  setWindowTitle("Demokratur");
}

Dialog::~Dialog() {
  delete board;
  delete thread;
  delete worker;
}

// private methods

void Dialog::createHorizontalGroupBox() {
  horizontalGroupBox = new QGroupBox("Eingabe:", this);
  QHBoxLayout* layout = new QHBoxLayout(this);

  lineEdits[0] = new QLineEdit(this);
  lineEdits[0]->setText("15");
  layout->addWidget(lineEdits[0]);

  lineEdits[1] = new QLineEdit(this);
  lineEdits[1]->setText("15");
  layout->addWidget(lineEdits[1]);

  lineEdits[2] = new QLineEdit(this);
  lineEdits[2]->setText("50");
  layout->addWidget(lineEdits[2]);

  thread = new QThread;
  worker = new Worker(board, 1000000000);
  worker->moveToThread(thread);

  connect(worker, SIGNAL(repaint()), this, SLOT(repaint()));
  connect(worker, SIGNAL(finished()), this, SLOT(finished()));
  connect(this, SIGNAL(setBoard(Board*)), worker, SLOT(setBoard(Board*)));
  connect(this, SIGNAL(start()), worker, SLOT(start()));
  connect(this, SIGNAL(stop()), worker, SLOT(stop()));
  thread->start();

  buttons[0] = new QPushButton("Start", this);
  QObject::connect(buttons[0], &QPushButton::clicked,
                   [this] { handleStartButton(); });
  layout->addWidget(buttons[0]);

  buttons[1] = new QPushButton("Stop", this);
  QObject::connect(buttons[1], &QPushButton::clicked,
                   [this] { handleStopButton(); });
  layout->addWidget(buttons[1]);
  buttons[1]->setEnabled(false);

  buttons[2] = new QPushButton("Pause", this);
  QObject::connect(buttons[2], &QPushButton::clicked,
                   [this] { handlePauseButton(); });
  layout->addWidget(buttons[2]);
  buttons[2]->setEnabled(false);

  horizontalGroupBox->setLayout(layout);
  horizontalGroupBox->setFixedHeight(58);
}

void Dialog::createVillageArea() {
  villageGroupBox = new QGroupBox("Dorf", this);
  villageGroupBox->setMinimumHeight(600);
  villageGroupBox->setMinimumWidth(600);
}

void Dialog::handleStartButton() {
  int x = lineEdits[0]->text().toInt();
  int y = lineEdits[1]->text().toInt();
  int cit = lineEdits[2]->text().toInt();

  if (reset) {
    board->reset(x, y, cit);
  }

  emit start();
  buttons[0]->setEnabled(false);
  buttons[1]->setEnabled(true);
  buttons[2]->setEnabled(true);

  lineEdits[0]->setEnabled(false);
  lineEdits[1]->setEnabled(false);
  lineEdits[2]->setEnabled(false);
}

void Dialog::handleStopButton() {
  reset = true;
  emit stop();
  buttons[0]->setEnabled(true);
  buttons[1]->setEnabled(false);
  buttons[2]->setEnabled(false);

  lineEdits[0]->setEnabled(true);
  lineEdits[1]->setEnabled(true);
  lineEdits[2]->setEnabled(true);
}

void Dialog::handlePauseButton() {
  reset = false;
  emit stop();
  buttons[0]->setEnabled(true);
  buttons[1]->setEnabled(false);
  buttons[2]->setEnabled(false);

  lineEdits[0]->setEnabled(false);
  lineEdits[1]->setEnabled(false);
  lineEdits[2]->setEnabled(false);
}

// public slots

void Dialog::finished() {
  std::cout << "finished" << std::endl;
  handleStopButton();
}

void Dialog::repaint() {
  update();
}

// overridden methods

void Dialog::paintEvent(QPaintEvent*) {
  int xPadding = 20;
  int yPadding = 90;
  double oneWidth = (size().width() - 2 * xPadding) / (double)board->getXDim();
  double oneHeight =
      (size().height() - yPadding - 20) / (double)board->getYDim();
  QPainter painter(this);

  for (int i = 0; i < board->getSize(); i++) {
    std::shared_ptr<Position> pos = board->getPosition(i);
    QRect rect =
        QRect((pos->getX() * oneWidth) + xPadding,
              (pos->getY() * oneHeight) + yPadding, oneWidth, oneHeight);
    painter.setPen(QPen(Qt::gray, 2));
    painter.drawRect(rect);
    if (pos->isOccupied()) {
      painter.fillRect(rect, *pos->getBaseEntity()->getBrush());
    } else {
      painter.fillRect(rect, Qt::white);
    }
  }
}

void Dialog::closeEvent(QCloseEvent* e) {
  thread->quit();
  e->accept();
}
