#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recordsform.h"

#define LOOP 750
#define INDICATOR_SIZE 31

#define WOLF_LEFT 180
#define WOLF_RIGHT 296
#define WOLF_Y 165

#define EGG_DY 73
const int eggs_rx[5] = {510, 492, 478, 462, 446};
const int eggs_lx[5] = {46, 61, 76, 91, 108};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(":/bg.jpg"));

    //Main display
    scene = new QGraphicsScene(0, 0, 572, 350, this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap(":/img/logo.png"));

    //Indicators
    indicator1 = new QGraphicsScene(0, 0, 31, 31);
    indicator2 = new QGraphicsScene(0, 0, 31, 31);
    ui->graphicsView_2->setScene(indicator1);
    ui->graphicsView_3->setScene(indicator2);

    indicator1->addItem(new Indicator());

    //Sounds
    bg_sound = new QMediaPlayer(this);
    bg_sound->setMedia(QUrl("qrc:/sounds/sound.wav"));

    game_sound = new QMediaPlayer(this);
    game_sound->setMedia(QUrl("qrc:/sounds/tap.wav"));

    egg_sound = new QMediaPlayer(this);
    egg_sound->setMedia(QUrl("qrc:/sounds/egg.wav"));

    lost_egg_sound = new QMediaPlayer(this);
    lost_egg_sound->setMedia(QUrl("qrc:/sounds/lost_egg.wav"));

    //Records
    records = new std::set<std::pair<QString, int>, srt>;
    QFile inputFile("records.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QStringList line = in.readLine().split("$");
          records->insert(std::pair<QString, int>(line[0],line[1].toInt()));
       }
       inputFile.close();
    }

    //Game
    gameLoop = new QTimer(this);
    connect(gameLoop, SIGNAL(timeout()),
            this, SLOT(Play()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Render()
{
    scene->clear();
    scene->addPixmap(QPixmap(":/img/game-bg.jpg"));

    //New Player
    scene->addItem(new Wolf(wolf_x));
    scene->addItem(new Basket(basket_pos));

    for(int i = 0; i < game->eggs->length(); i++){
        Egg *this_egg = game->eggs->value(i);
        int ex, ey;

        if(this_egg->layer == 3 || this_egg->layer == 4)
            ex = eggs_rx[this_egg->pos - 1];
        else
            ex = eggs_lx[this_egg->pos - 1];

        if(this_egg->layer == 1 || this_egg->layer == 4)
            ey = EGG_DY + 119 + 10 * (this_egg->pos - 1);
        else
            ey = 119 + 10 * (this_egg->pos - 1);

        //New egg
        scene->addItem(new G_Egg(ex, ey));
    }

    //Chiks
    for(int i = 0; i < game->getLife(); i++){
        scene->addItem(new Chick(326 + i*40));
    }

    //Lost egg
    if(tmp_lost_egg)
        scene->addItem(new Splinter(tmp_lost_egg == 1));
    tmp_lost_egg = 0;

    //Score
    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setPos(250,40);
    io->setHtml("<font face='Consolas' size='48'>" + QString::number(game->getScore()) + "</font>");
    scene->addItem(io);
}

void MainWindow::movePlayer(int key){
    if(!play) return;

    game_sound->play();

    //Player position
    switch (key) {
    case Qt::Key_A:
        wolf_x = true;
        basket_pos = 1;
        game->tapEvent(true, false);
        break;
    case Qt::Key_Q:
        wolf_x = true;
        basket_pos = 2;
        game->tapEvent(true, true);
        break;
    case Qt::Key_E:
        wolf_x = false;
        basket_pos = 4;
        game->tapEvent(false, true);
        break;
    case Qt::Key_D:
        wolf_x = false;
        basket_pos = 3;
        game->tapEvent(false, false);
        break;
    default:
        return;
        break;
    }

    //Render
    Render();
}

void MainWindow::Play()
{
    game->Play();
    Render();

    if(game->getScore() >= 5 && game->getScore() < 10)
        gameLoop->setInterval(500);
    else if(game->getScore() > 10)
        gameLoop->setInterval(250);
}

void MainWindow::lostEgg(bool left)
{
    lost_egg_sound->play();
    tmp_lost_egg = left ? 1 : 2;
}

void MainWindow::GameOver()
{
    gameLoop->stop();
    bg_sound->stop();
    indicator2->clear();

    //scene->clear();
    //scene->addPixmap(QPixmap(":/img/GameOver.png"));

    writeRecord(game->getScore());

    play = false;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    movePlayer(event->key());
}

Wolf::Wolf(bool left) : QGraphicsPixmapItem(0)
{
    if(left){
        setPixmap(QPixmap(":/img/wolf/wolf-p-0.png"));
        setPos(WOLF_LEFT, WOLF_Y);
    }else{
        setPixmap(QPixmap(":/img/wolf/wolf-p-1.png"));
        setPos(WOLF_RIGHT, WOLF_Y);
    }
}

Basket::Basket(int pos) : QGraphicsPixmapItem(0)
{
    switch (pos) {
    case 1:
        setPixmap(QPixmap(":/img/basket/basket-p-0-0.png"));
        setPos(125, 236);
        break;
    case 2:
        setPixmap(QPixmap(":/img/basket/basket-p-0-1.png"));
        setPos(128, 158);
        break;
    case 3:
        setPixmap(QPixmap(":/img/basket/basket-p-1-0.png"));
        setPos(361, 242);
        break;
    case 4:
        setPixmap(QPixmap(":/img/basket/basket-p-1-1.png"));
        setPos(370, 167);
        break;
    default:
        break;
    }
}

G_Egg::G_Egg(int x, int y) : QGraphicsPixmapItem(0)
{
    if(x < 286)
        setPixmap(QPixmap(":/img/egg/egg-r.png"));
    else
        setPixmap(QPixmap(":/img/egg/egg.png"));

    setPos(x, y);
}

void MainWindow::on_pushButton_clicked()
{
    movePlayer(Qt::Key_Q);
}

void MainWindow::on_pushButton_2_clicked()
{
    movePlayer(Qt::Key_A);
}

void MainWindow::on_pushButton_3_clicked()
{
    movePlayer(Qt::Key_E);
}

void MainWindow::on_pushButton_4_clicked()
{
    movePlayer(Qt::Key_D);
}

void MainWindow::on_pushButton_5_clicked()
{
    newGame(true);
}

void MainWindow::on_pushButton_6_clicked()
{
    newGame(false);
}

Indicator::Indicator() : QGraphicsEllipseItem(0)
{
    QColor color = QColor(255, 222, 0);
    setBrush(color);
    setRect(0, 0, INDICATOR_SIZE, INDICATOR_SIZE);
    setPos(0, 0);
}

Chick::Chick(int x) : QGraphicsPixmapItem(0)
{
    setPixmap(QPixmap(":/img/loss/loss.png"));
    setPos(x, 114);
}

Splinter::Splinter(bool left) : QGraphicsPixmapItem(0)
{
    if(left){
        setPixmap(QPixmap(":/img/loss/lost_egg_l.png"));
        setPos(93, 312);
    }else{
        setPixmap(QPixmap(":/img/loss/lost_egg_r.png"));
        setPos(443, 312);
    }
}

void MainWindow::newGame(bool type)
{
    if(!play){
        game = new Game(type, this);
        gameLoop->start(LOOP);

        connect(game, SIGNAL(collectEgg()), egg_sound, SLOT(play()));
        connect(game, SIGNAL(lostEgg(bool)), this, SLOT(lostEgg(bool)));
        connect(game, SIGNAL(GameOver()), this, SLOT(GameOver()));

        indicator2->addItem(new Indicator());
        bg_sound->play();
        Render();

        play = true;
    }
}

void MainWindow::writeRecord(int r)
{
    QTime currTime = QTime::currentTime();
    records->insert(std::pair<QString, int>(currTime.toString("hh:mm:ss"), r));

    QFile file("records.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream ts(&file);

        for ( std::set<std::pair<QString, int>>::const_iterator it = records->begin();
             it != records->end();
             it++)
        {
            ts << it->first << "$" << it->second << "\n";
        }
    }
    file.close();
}

void MainWindow::on_pushButton_7_clicked()
{
    RecordsForm rf;
    rf.setModal(true);
    rf.exec();
}
