#ifndef GFXSCENE_H
#define GFXSCENE_H

#include <QtGui/QGraphicsScene>
#include <QtCore/QTimer>

class gfxScene: public QGraphicsScene
{
  Q_OBJECT

  public:
    explicit gfxScene(QObject *parent = 0);

    bool isPaused() { return m_paused; }
    int boardWidth() { return m_width; }
    int boardHeight() { return m_height; }

    void play();
    void pause();

  signals:
    void signalLog(QString msg);
    void signalGameStarted();
    void signalGameEnded();

  public slots:
    void slotNewGame(int turn, int width, int height, int hunters, int animals);
    void slotNextTurn();

  private slots:
    void slotPredatorCaged();

  private:
    bool m_paused;
    int m_width;
    int m_height;
    int m_turns;
    int m_predators;
    int m_caged;
    QTimer m_tmrTurns;
};

#endif // GFXSCENE_H
