#include <dialog.h>

Dialog::Dialog() {
  board = new Board(15, 15, 50);
  reset = false;
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
  delete[] buttons[3];
  delete[] lineEdits[3];

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
  lineEdits[0]->setText("15");
  layout->addWidget(lineEdits[0]);

  lineEdits[1] = new QLineEdit;
  lineEdits[1]->setText("15");
  layout->addWidget(lineEdits[1]);

  lineEdits[2] = new QLineEdit;
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

  buttons[0] = new QPushButton("Start");
  QObject::connect(buttons[0], &QPushButton::clicked,
                   [this] { handleStartButton(); });
  layout->addWidget(buttons[0]);

  buttons[1] = new QPushButton("Stop");
  QObject::connect(buttons[1], &QPushButton::clicked,
                   [this] { handleStopButton(); });
  layout->addWidget(buttons[1]);
  buttons[1]->setEnabled(false);

  buttons[2] = new QPushButton("Pause");
  QObject::connect(buttons[2], &QPushButton::clicked,
                   [this] { handlePauseButton(); });
  layout->addWidget(buttons[2]);
  buttons[2]->setEnabled(false);

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

  for (int i = 0; i < board->getYDim(); i++) {
    for (int j = 0; j < board->getXDim(); j++) {
      QRect rect =
          QRect((j * oneWidth) + x, (i * oneHeight) + y, oneWidth, oneHeight);
      painter.setPen(QPen(Qt::gray, 2));
      painter.drawRect(rect);
      painter.fillRect(rect, Qt::white);
    }
  }
  std::vector<std::shared_ptr<BaseEntity>>* entities = board->getBaseEntities();
  for (std::shared_ptr<BaseEntity> entity : *entities) {
    std::shared_ptr<Position> pos = entity->getPosition();

    QRect rect = QRect((pos->getX() * oneWidth) + x,
                       (pos->getY() * oneHeight) + y, oneWidth, oneHeight);
    painter.setPen(QPen(Qt::gray, 2));
    painter.drawRect(rect);
    painter.fillRect(rect, entity->getColor());
  }
}
