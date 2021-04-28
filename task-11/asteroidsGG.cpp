#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <iostream>
#include<random>
#include <memory>
//#include <functional>


using namespace sf;

const int W = 1200;
const int H = 800;

const float DEGTORAD = 0.017453f;
bool close = false;

class Animation
{
//private:
public:
  float Frame, speed;
  Sprite sprite;
  std::vector<IntRect> frames;

public:
  Animation() {}

  Animation(Texture &t, int x, int y, int w, int h, int count, float Speed)
  {
    Frame = 0.0;
    speed = Speed;

    for (int i = 0; i < count; i++)
      frames.push_back(IntRect(x + i * w, y, w, h));

    sprite.setTexture(t);
    sprite.setOrigin(w / 2, h / 2);
    sprite.setTextureRect(frames[0]);
  }

  void update()
  {
    Frame += speed;
    int n = frames.size();
    if (Frame >= n)
      Frame -= n;
    if (n > 0)
      sprite.setTextureRect(frames[int(Frame)]);
  }

  bool isEnd()
  {
    return Frame + speed >= frames.size();
  }

  /*void set_sprite(Sprite sprite_)
  {
    sprite=sprite_;
  }  
  
  Sprite get_sprite()
  {
    return sprite;
  }
*/
  void set_speed(float speed_)
  {
    speed=speed_;
  }
  float get_speed()
  {
    return speed;
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // void operator=(const Animation& other)
  // {
  //   Frame = other.Frame;
  //   speed = other.speed;
  //   sprite = other.sprite;
  //   frames = other.frames;
  // }
};

class Entity
{
private:
  float x, y, dx, dy, R, angle;
  int life;
  std::string name;
  

public:
Animation anim;
  Entity()
  {
    life = 1;
  }

  void set_x(float x_)
  {
    x=x_;
  }
  float get_x()
  {
    return x;
  }

  void set_dx(float dx_)
  {
    dx=dx_;
  }
  float get_dx()
  {
    return dx;
  }

  void set_y(float y_)
  {
    y=y_;
  }
  float get_y()
  {
    return y;
  }

  void set_dy(float dy_)
  {
    dy=dy_;
  }
  float get_dy()
  {
    return dy;
  }

  void set_R(float R_)
  {
    R=R_;
  }
  float get_R()
  {
    return R;
  }

  void set_angle(float angle_)
  {
    angle=angle_;
  }
  float get_angle()
  {
    return angle;
  }

  void set_life(int life_)
  {
    life=life_;
  }
  float get_life()
  {
    return life;
  }

  void set_name(std::string name_)
  {
    name=name_;
  }
  std::string get_name()
  {
    return name;
  }

  void set_anim(Animation anim_)
  {
    anim = anim_;
  }
  Animation get_anim()
  {
    return anim;
  }

  void add_life(int life_)
  {
    life += life_;
  }
  void sub_life(int life_)
  {
    life -= life_;
  }


  void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1)
  {
    anim = a;
    x = X;
    y = Y;
    angle = Angle;
    R = radius;
  }

  virtual void update(){};

  void draw(RenderWindow &app)
  {
    // (anim.get_sprite()).setPosition(x, y);
    // (anim.get_sprite()).setRotation(angle + 90);
    // app.draw(anim.get_sprite());
    anim.sprite.setPosition(x,y);
    anim.sprite.setRotation(angle+90);
    app.draw(anim.sprite);

    CircleShape circle(R);
    circle.setFillColor(Color(255, 0, 0, 170));
    circle.setPosition(x, y);
    circle.setOrigin(R, R);
    //app.draw(circle);
  }

  virtual ~Entity(){};
};

class asteroid : public Entity
{
public:
  asteroid()
  {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_real_distribution<> un_distrib(-4, 4);
    this->set_dx(un_distrib(mersenne));
    //// dx = rand() % 8 - 4;
    //// dy = rand() % 8 - 4;
    // this->set_dx(rand() % 8 - 4);
    // this->set_dy(rand() % 8 - 4);
    this->set_dy(un_distrib(mersenne));
    set_name("asteroid");
  }

public:
  void update()
  {
    //x += dx;
    //y += dy;
    this->set_x(this->get_x() + this->get_dx());
    this->set_y(this->get_y() + this->get_dy());


    if (this->get_x() > W) 
      this->set_x(0);
    if (this->get_x() < 0)
      this->set_x(W);
    if (this->get_y() > H)
      this->set_y(0);
    if (this->get_y() < 0)
      this->set_y(H);
  }
};

class bullet : public Entity
{
public:
  bullet()
  {
    this->set_name("bullet");
  }

  void update()
  {
    this->set_dx(cos(this->get_angle() * DEGTORAD) * 6);
    this->set_dy(sin(this->get_angle() * DEGTORAD) * 6);
    //dy = sin(angle * DEGTORAD) * 6;
    // angle+=rand()%7-3;  /*try this*/
    // x += dx;
    // y += dy;
    this->set_x(this->get_x() + this->get_dx());
    this->set_y(this->get_y() + this->get_dy());

    if (this->get_x() > W || this->get_x() < 0 || this->get_y() > H || this->get_y() < 0)
      this->set_life(0);//this->set_life(this->get_life() - 1);
  }
};

class player : public Entity
{
private:
  bool thrust;
  int scores;
public:
  player()
  {
    this->set_name("player");
    scores = 0;
    this->set_life(3);
  }

  void set_thrust(bool thrust_)
  {
    thrust = thrust_;
  }
  bool get_thrust()
  {
    return thrust;
  }
  void set_scores(int scores_)
  {
    scores = scores_;
  }
  void add_scores(int scores_)
  {
    scores += scores_;
  }
  int get_scores()
  {
    return scores;
  }
  //sub_life add_life//////////////////////////////////////////////////////////// 
  // void add_life(int life_)
  // {
  //   scores += life_;
  // }
  // void sub_life(int life_)
  // {
  //   life -= life_;
  // }

  void update()
  {
    if (thrust)
    {
      //dx += cos(angle * DEGTORAD) * 0.2;
      this->set_dx(this->get_dx() + cos(this->get_angle() * DEGTORAD) * 0.2);
      //dy += sin(angle * DEGTORAD) * 0.2;
      this->set_dy(this->get_dy() + sin(this->get_angle() * DEGTORAD) * 0.2);
    }
    else
    {
      //dx *= 0.99;
      this->set_dx(this->get_dx() * 0.99);
      //dy *= 0.99;
      this->set_dy(this->get_dy() * 0.99);
      
    }

    int maxSpeed = 15;
    float speed = sqrt(this->get_dx() * this->get_dx() + this->get_dy() * this->get_dy());
    if (speed > maxSpeed)
    {
      //dx *= maxSpeed / speed;
      this->set_dx(this->get_dx() * maxSpeed / speed);//(this->get_anim()).get_speed());
      //dy *= maxSpeed / speed;
      this->set_dx(this->get_dx() * maxSpeed / speed);//(this->get_anim()).get_speed());
      
    }

    // x += dx;
    // y += dy;
    this->set_x(this->get_x() + this->get_dx());
    this->set_y(this->get_y() + this->get_dy());


    if (this->get_x() > W) this->set_x(0);
    if (this->get_x() < 0) this->set_x(W);
    if (this->get_y() > H) this->set_y(0);
    if (this->get_y() < 0) this->set_y(H);
  }
};

bool isCollide(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
  return ((b->get_x() - a->get_x()) * (b->get_x() - a->get_x()) +
      (b->get_y() - a->get_y()) * (b->get_y() - a->get_y())) <
      ((a->get_R() + b->get_R()) * (a->get_R() + b->get_R()));
}



class Interface
{
public:
  float x, y;
  std::string name;
  
  Sprite sprite;
  Color color;
  sf::Text text;
public:
  Interface() : x(W/10), y(H/10), color(Color(175, 180, 240))
  { 
    name = "interface";
  }
  Interface(float x_,float y_, Color color_): x(x_), y(y_), color(color_)
  {
    name= "interface";
  }

  //virtual void update(){};


  void set_position(int x_,int y_)
  {
    x=x_;
    y=y_;
  }

  auto get_x()
  {
    return x;
  }
  auto get_y()
  {
    return y;
  }

  /*
  void draw_interface(RenderWindow &app)
  {
    sf::Font font;
    if(!font.loadFromFile("images/arial.ttf"))
    {
      std::cout<<"very bad";
    }
    RectangleShape rectangle(Vector2f(x, y));
    //rectangle.move(x,y);
    rectangle.setFillColor(color);
    app.draw(rectangle);
    // state_.move(0,0);
    sf::Text text("Nice", font, 50);
    app.draw(text);
  }
  */
};


class Interface_score : public Interface
{
//public:
  
public:
  Interface_score() //: x(W/10), y(H/10), color(Color(175, 180, 240))
  { 
    Interface();
    name = "interface_score";
    // Texture t;
    // t.loadFromFile("images/star.jpg");
    // sprite.setTexture(t);
    //sprite.setOrigin(w / 2, h / 2);
    //sprite.setTextureRect(frames[0]);

  }
  Interface_score(float x_, float y_, Color color_)//: x(x_), y(y_), color(color_)
  {
    //Interface(x_, y_, color_);
    x = x_;
    y = y_;
    color = color_;
    name= "interface_score";
    // Texture t;
    // t.loadFromFile("images/star.jpg");
    // sprite.setTexture(t);
    
  }

  void draw(RenderWindow &app, int score = 0)
  {
    sprite.setPosition(this->x, this->y);
    Texture t;
    t.loadFromFile("images/star.png");
    // t.loadFromFile("images/fire_red.png");
    sprite.setTexture(t);
    // sprite.setTextureRect(IntRect(this->x, this->y, 100, 300));
    app.draw(sprite);

    sf::Font font;
    if(!font.loadFromFile("images/arial.ttf"))
    {
      std::cout<<"very bad";
    }
    ////RectangleShape rectangle(Vector2f(30, 30));//(this->x, this->y));
    //rectangle.move(x,y);
    ////rectangle.setFillColor(color);
    //app.draw(rectangle);
    // state_.move(0,0);
    sf::Text text(std::to_string(score), font, 20);
    text.setPosition(this->x + 30, this->y + 40);
    text.setFillColor(Color(0, 0, 0));
    app.draw(text);
  }
  


  
};



class Interface_health : public Interface
{
//public:
  
public:
  Interface_health() //: x(W/10), y(H/10), color(Color(175, 180, 240))
  { 
    Interface();
    name = "interface_health";
    // Texture t;
    // t.loadFromFile("images/star.jpg");
    // sprite.setTexture(t);
    //sprite.setOrigin(w / 2, h / 2);
    //sprite.setTextureRect(frames[0]);

  }
  Interface_health(float x_, float y_, Color color_)//: x(x_), y(y_), color(color_)
  {
    //Interface(x_, y_, color_);
    x = x_;
    y = y_;
    color = color_;
    name= "interface_health";
    // Texture t;
    // t.loadFromFile("images/star.jpg");
    // sprite.setTexture(t);
    
  }

  void draw(RenderWindow &app, int live = 0)
  {
    const int w = 100;
    sprite.setPosition(this->x, this->y);
    Texture t;
    t.loadFromFile("images/hearts.png");
    // t.loadFromFile("images/fire_red.png");
    t.setSmooth(true);
    
    //Animation sPlayer(t, 40, 0, 40, 40, 1, 0);
    sprite.setTextureRect(IntRect(x + (3 - live)*w, y, w, w));
  
    sprite.setTexture(t);
    // sprite.setTextureRect(IntRect(this->x, this->y, 100, 300));
    app.draw(sprite);

    sf::Font font;
    if(!font.loadFromFile("images/arial.ttf"))
    {
      std::cout<<"very bad";
    }
    ////RectangleShape rectangle(Vector2f(30, 30));//(this->x, this->y));
    //rectangle.move(x,y);
    ////rectangle.setFillColor(color);
    //app.draw(rectangle);
    // state_.move(0,0);
    //sf::Text text(std::to_string(score), font, 20);
    //text.setPosition(this->x + 30, this->y + 40);
    //text.setFillColor(Color(0, 0, 0));
    app.draw(text);
  }
  


  
};




int main()
{
  // srand(time(0));
  // std::random_device rd;
  // std::mt19937 mersenne(rd());
  // std::uniform_real_distribution<> un_distrib(0, 1);
  std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_int_distribution<> un_distrib_W(0, W);
    std::uniform_int_distribution<> un_distrib_H(0, H);
    std::uniform_real_distribution<> un_distrib_360(0, 360);

  RenderWindow app(VideoMode(W, H), "Asteroids!");
  app.setFramerateLimit(60);

  Texture t1, t2, t3, t4, t5, t6, t7;
  t1.loadFromFile("images/spaceship.png");
  t2.loadFromFile("images/background.jpg");
  t3.loadFromFile("images/explosions/type_C.png");
  t4.loadFromFile("images/rock.png");
  t5.loadFromFile("images/fire_blue.png");
  t6.loadFromFile("images/rock_small.png");
  t7.loadFromFile("images/explosions/type_B.png");

  t1.setSmooth(true);
  t2.setSmooth(true);

  Sprite background(t2);

  Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
  Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
  Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
  Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
  Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
  Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
  Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);

  //std::unique_ptr<Entity> item(new Entity);

  std::vector<std::shared_ptr<Entity>> entities;
  // std::list<std::reference_wrapper<Entity>> entities;
  // //std::list<Entity *> entities;

  // //player *p = new player();
  // //std::unique_ptr<player> p(new player);
//  std::shared_ptr<Entity> p(new player);//
  // player p0();
  // Entity* p1 = *p0;
  // std::unique_ptr<Entity> p = p1;
  // entities.push_back(new player());
  // entities
  // p->settings(sPlayer, 200, 200, 0.0, 20);
//  entities.push_back(p); //
  


  for (int i = 0; i < 2; i++)
  {
    //asteroid *a = new asteroid();
    std::shared_ptr<Entity> a(new asteroid);

    // std::random_device rd;
    // std::mt19937 mersenne(rd());
    // std::uniform_int_distribution<> un_distrib_W(0, W);
    // std::uniform_int_distribution<> un_distrib_H(0, H);
    // std::uniform_int_distribution<> un_distrib_360(0, 360);
    a->settings(sRock, un_distrib_W(mersenne), un_distrib_H(mersenne), un_distrib_360(mersenne), 25);
    //a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
    //a->settings(sRock, 300, 300, 23, 25);
    //entities.push_back(std::static_pointer_cast<>(a));
    entities.push_back(a);
  }

  std::shared_ptr<player> p(new player);
  p->settings(sPlayer, 200, 200, 0.0, 20);
  entities.push_back(p);


  /////main loop/////
  while (app.isOpen() && (!close))
  {
    Event event;
    while (app.pollEvent(event))
    {
      if (event.type == Event::Closed)
        app.close();

      if (event.type == Event::KeyPressed)
        if (event.key.code == Keyboard::Space)
        {
          //bullet *b = new bullet();
          std::shared_ptr<Entity> b(new bullet);
          b->settings(sBullet, p->get_x(), p->get_y(), p->get_angle(), 10);
          entities.push_back(b);
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Right))
      p->set_angle(p->get_angle() + 3.0);
    if (Keyboard::isKeyPressed(Keyboard::Left))
      p->set_angle(p->get_angle() - 3.0);
    if (Keyboard::isKeyPressed(Keyboard::Up))
      p->set_thrust(true);
      //(std::dynamic_pointer_cast<player>(p))->set_thrust(true); //???????????????
    else
      p->set_thrust(false);
      //(static_cast<player*>(p))->set_thrust(false);//???
      // (std::dynamic_pointer_cast<player>(p))->set_thrust(false);

    for (std::shared_ptr<Entity> a : entities)
      for (auto b : entities)
      {
        if (a->get_name() == "asteroid" && b->get_name() == "bullet")//
          if (isCollide(a,b))//(isCollide(std::dynamic_pointer_cast<asteroid>(a), std::dynamic_pointer_cast<bullet>(b)))
          {
            a->set_life(0);
            b->set_life(0);

            // (std::dynamic_pointer_cast<player>(entities[0]))->set_scores(
            //     (std::dynamic_pointer_cast<player>(entities[0]))->get_scores() + 10
            // );

            //Entity *e = new Entity();
            std::shared_ptr<Entity> e(new Entity);
            e->settings(sExplosion, a->get_x(), a->get_y());
            e->set_name("explosion");
            entities.push_back(e);

            for (int i = 0; i < 2; i++)
            {

              if (a->get_R() == 15)
              {
                p->add_scores(10);
                // (std::dynamic_pointer_cast<player>(entities[0]))->set_scores(
                //     (std::dynamic_pointer_cast<player>(entities[0]))->get_scores() + 10);
                continue;

              }
              p->add_scores(5);
              // (std::dynamic_pointer_cast<player>(entities[0]))->set_scores(
              //     (std::dynamic_pointer_cast<player>(entities[0]))->get_scores() + 5);
                
              //Entity *e = new asteroid();
              std::shared_ptr<Entity> e2(new asteroid);

              // std::random_device rd;
              // std::mt19937 mersenne(rd());
              // std::uniform_real_distribution<> un_distrib(0, 360);

              e2->settings(sRock_small, a->get_x(), a->get_y(), un_distrib_360(mersenne), 15);
              // e->settings(sRock_small, a->get_x(), a->get_y(), rand() % 360, 15);
              entities.push_back(e2);
            }
          }

        if (a->get_name() == "player" && b->get_name() == "asteroid")
          if (isCollide(a, b))//std::dynamic_pointer_cast<asteroid>(
          {
            b->set_life(0);

            //Entity *e = new Entity();
            std::shared_ptr<Entity> e(new Entity);
            e->settings(sExplosion_ship, a->get_x(), a->get_y());
            e->set_name("explosion");
            entities.push_back(e);

            if(p->get_life() > 1)
            {
              p->sub_life(1);
              p->settings(sPlayer, W / 2, H / 2, 0, 20);
              p->set_dx(0);
              p->set_dy(0);
            }
            else
            {
              close = true;
            }
            //a->set_life(a->get_life() - 1);///////////////////////////////////////////////////////////

            
          }
      }

    // if (p->get_thrust())
    //   p->set_anim(sPlayer_go);
    // else
    //   p->set_anim(sPlayer);

    // if (std::dynamic_pointer_cast<player>(p)->get_thrust())  p->anim = sPlayer_go;
    // else   p->anim = sPlayer;
    if (p->get_thrust())  p->anim = sPlayer_go;
    else   p->anim = sPlayer;


    for (auto e : entities)
      if (e->get_name() == "explosion")
        if ((e->get_anim()).isEnd())
          e->set_life(0);


    // std::random_device rd;
    // std::mt19937 mersenne(rd());
    // std::uniform_int_distribution<> un_distrib(0, 100);
    // if (un_distrib(mersenne) % 10 == 0)////////////
    if (un_distrib_W(mersenne) % 50 == 0)///////////////////////////////////////////////////////////////////////////
    {
      // asteroid *a = new asteroid();
      std::shared_ptr<Entity> a(new asteroid);

      // std::random_device rd;
      // std::mt19937 mersenne(rd());
      // std::uniform_real_distribution<> un_distrib_H(0, H);
      // std::uniform_real_distribution<> un_distrib_360(0, 360);

      a->settings(sRock, 0, un_distrib_H(mersenne), un_distrib_360(mersenne), 25);
      // a->settings(sRock, 0, rand() % H, rand() % 360, 25);
      entities.push_back(a);
    }

    for (auto i = entities.begin(); i != entities.end();)
    {
      std::shared_ptr<Entity> e = *i;
      // Entity e = *i;

      e->update();////
      //(e->get_anim()).update();
      e->anim.update();

      if (e->get_life() == 0)
      {
        i = entities.erase(i);
        //delete e;
      }
      else
        i++;
    }


    // //Interface_score in_sc(10,10, Color(175, 180, 240));
    // Sprite sprite;
    // Texture t;
    // t.loadFromFile("images/star.jpg");
    // sprite.setTexture(t);
    // // sprite.setPosition(100,100);
    // app.draw(sprite);
    //////draw//////
    app.draw(background);
    for (auto i : entities)
      i->draw(app);
    p->draw(app);

    Interface_score insc(W-100,0, Color(175, 180, 240));
    //Sprite sprite;
    //Texture t;
    //t.loadFromFile("images/star.jpg");
    //insc.sprite.setTexture(t);
    // sprite.setPosition(100,100);
    // app.draw(insc.sprite);
    insc.draw(app, p->get_scores());

    Interface_health inhe(0,0, Color(175, 180, 240));
    inhe.draw(app, p->get_life());
   
    app.display();
  }

  // std::cout << "score: " << 
  //     (std::dynamic_pointer_cast<player>(entities[0]))->get_scores() << std::endl;
  std::cout << "score: " << 
      p->get_scores() << std::endl;

  return 0;
}
