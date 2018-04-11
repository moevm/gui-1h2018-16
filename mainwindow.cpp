#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#define LOOP 1000

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

    scene = new QGraphicsScene(0, 0, 572, 350, this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap(":/img/game-bg.jpg"));

    play = false;

    ui->label_2->setStyleSheet("color: yellow");

    bg_sound = new QMediaPlayer(this);
    bg_sound->setMedia(QUrl("qrc:/sounds/sound.wav"));

    game_sound = new QMediaPlayer(this);
    game_sound->setMedia(QUrl("qrc:/sounds/tap.wav"));

    egg_sound = new QMediaPlayer(this);
    egg_sound->setMedia(QUrl("qrc:/sounds/egg.wav"));

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
    qDebug() << "Score: " << game->getScore() << " | lifes: " << game->getLife();
    //Game over check...

    Render();
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
        setPos(131, 160);
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

void MainWindow::newGame(bool type)
{
    if(!play){
        game = new Game(type, this);
        gameLoop->start(LOOP);

        connect(game, SIGNAL(collectEgg()), egg_sound, SLOT(play()));
        ui->label_3->setStyleSheet("color: yellow");
        bg_sound->play();

        play = true;
    }
}
