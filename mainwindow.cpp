#include "mainwindow.h"
#include "ui_mainwindow.h"

#define WOLF_LEFT 140
#define WOLF_RIGHT 240
#define WOLF_Y 198

Game *game;
Wolf *wolf;
Basket *basket;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(":/bg.jpg"));

    scene = new QGraphicsScene(0, 0, 572, 350, this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap(":/img/game-bg.jpg"));

    game = new Game(true);
    wolf = new Wolf();
    basket = new Basket();

    scene->addItem(wolf);
    scene->addItem(basket);

    /*gameLoop = new QTimer(this);
    connect(gameLoop, SIGNAL(timeout()),
            game, SLOT(Play()));
    gameLoop->start(1000);*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

Wolf::Wolf() : QGraphicsPixmapItem(0)
{
    setPixmap(QPixmap(":/img/wolf/wolf-p-0.png"));
    setPos(WOLF_LEFT, WOLF_Y);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Wolf::advance(int phase)
{
    if(phase){
        if(left){
            setPixmap(QPixmap(":/img/wolf/wolf-p-0.png"));
            setPos(WOLF_LEFT, WOLF_Y);
        }else{
            setPixmap(QPixmap(":/img/wolf/wolf-p-1.png"));
            setPos(WOLF_RIGHT, WOLF_Y);
        }
    }
}

void Wolf::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case 97:
    case 103:
        left = true;
        game->tapEvent(true, basket->top);
        break;
    case 99:
    case 105:
        left = false;
        game->tapEvent(false, basket->top);
        break;
    default:
        break;
    }
}

Basket::Basket() : QGraphicsPixmapItem(0)
{
    setPixmap(QPixmap(":/img/basket/basket-p-0-1.png"));
    setPos(100, 150);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Basket::advance(int phase)
{

}

void Basket::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case 103:
    case 105:
        top = true;
        game->tapEvent(wolf->left, true);
        break;
    case 97:
    case 99:
        top = false;
        game->tapEvent(wolf->left, false);
        break;
    default:
        break;
    }
}
