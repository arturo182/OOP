#include "gfxScene.h"

#include "itmHunter.h"
#include "itmPredator.h"
#include "itmMellow.h"
#include "HuntersApp.h"

#include <QtCore/QDebug>
#include <QtGui/QSound>

gfxScene::gfxScene(QObject *parent): QGraphicsScene(parent)
{
  m_paused = false;
  connect(&m_tmrTurns, SIGNAL(timeout()), this, SLOT(slotNextTurn()));
}

void gfxScene::play()
{
  if(m_paused) {
    m_tmrTurns.start();
    m_paused = false;
  }
}

void gfxScene::pause()
{
  if(!m_paused) {
    m_tmrTurns.stop();
    m_paused = true;
  }
}

void gfxScene::slotNewGame(int turn, int width, int height, int hunters, int animals)
{
  m_tmrTurns.stop();
  m_turns = 0;
  clear();

  emit signalLog("<b>Witamy w kolejnym odcinku programy \"Hunters\", czas rozpocząć nową grę!</b>");
  emit signalLog("Pozwolę sobię na szybko przypomnieć zasady naszej gry:");

  m_width = width;
  m_height = height;

  addRect(0, 0, width * 24, height * 24, QPen(QColor(13, 35, 0), 2), QBrush(QPixmap(qApp->applicationDirPath() + "/data/grass.png")));
  emit signalLog(QString("Gra rozgrywa się na planszy o rozmiarach %1x%2.").arg(width).arg(height));

  emit signalLog(QString("Na planszy umieszczamy %1 %2.").arg(hunters).arg((hunters > 1)?"naganiaczy":"naganiacza"));
  for(int i = 0; i < hunters; i++) {
    itmHunter *hunter = new itmHunter();
    connect(hunter, SIGNAL(signalLog(QString)), this, SIGNAL(signalLog(QString)));

    int x = (qrand() % width) * 24;
    int y = (qrand() % height) * 24;

    hunter->setPos(x, y);
    addItem(hunter);
  }

  m_predators = animals;
  m_caged = 0;

  QString msg = QString("Na planszy umieszczamy %1 %2: ").arg(animals).arg((animals > 1)?"dzikich zwierząt":"dzikie zwierzę");
  for(int i = 0; i < animals; i++) {
    itmPredator *pred = new itmPredator();
    connect(pred, SIGNAL(signalLog(QString)), this, SIGNAL(signalLog(QString)));
    connect(pred, SIGNAL(signalCaged()), this, SLOT(slotPredatorCaged()));

    msg.append(pred->genetivus());
    msg.append(", ");

    int x = (qrand() % width) * 24;
    int y = (qrand() % height) * 24;

    pred->setPos(x, y);
    addItem(pred);
  }

  msg.chop(2);
  msg.append(".");

  emit signalLog(msg);
  emit signalLog("Naganiacze łapią dzikie zwierzęta w klatki.");

  int mellow = qrand() % qRound(animals * 1.5);
  msg = QString("Na planszy umieszczamy %1 %2: ").arg(mellow).arg((mellow > 1)?"łagodnych zwierząt":"łagodne zwierzę");
  for(int i = 0; i < mellow; i++) {
    itmMellow *mell = new itmMellow();
    connect(mell, SIGNAL(signalLog(QString)), this, SIGNAL(signalLog(QString)));

    msg.append(mell->genetivus());
    msg.append(", ");

    int x = (qrand() % width) * 24;
    int y = (qrand() % height) * 24;

    mell->setPos(x, y);
    addItem(mell);
  }

  msg.chop(2);
  msg.append(".");

  emit signalLog(msg);
  emit signalLog("Dzikie zwierzęta zjadają łagodne zwierzęta.");

  m_tmrTurns.setInterval(turn);
  emit signalLog(QString("Każda runda trwa %1 ms.").arg(turn));


  emit signalLog("Gra kończy się gdy wszystkie dzikie zwierzęta zostaną złapane.");

  m_tmrTurns.start();
  emit signalLog("<b>START!</b>");

  emit signalGameStarted();
}

void gfxScene::slotNextTurn()
{
  m_turns++;

  emit signalLog(QString("<span style='color: gray;'>Nowa tura (%1)!</span>").arg(m_turns));
  foreach(QGraphicsItem *item, items()) {
    if(item->type() != QGraphicsRectItem::Type) {
      itmPawn *pawn = static_cast<itmPawn*>(item);
      pawn->makeMove();
    }
  }
}

void gfxScene::slotPredatorCaged()
{
  m_caged++;

  if(m_caged == m_predators) {
    emit signalLog("<b>KONIEC GRY!</b>");
    emit signalGameEnded();
    QSound::play(qApp->applicationDirPath() + "/data/sounds/the_end.wav");
  } else {
    int left = m_predators - m_caged;
    emit signalLog(QString("Na wolności %1 %2 %3.").arg((left == 1)?"pozostaje":"pozostają").arg(left).arg((left == 1)?"dzikie zwierzę":"dzikich zwierzęt"));
  }
}
