#pragma once
#include "minion.hh"
#include "map.hh"

namespace ed
{

class Command
{
public:
  Command(){}
  virtual ~Command() {};
  virtual float execute(Minion &minion, Map &map) = 0;
};

class CmdMoveRight : public Command
{
public:
  CmdMoveRight(){}
  virtual float execute(Minion &minion, Map &map)
  {
    return minion.move(MoveDir::R, map); // TODO:
  }
};
class CmdMoveLeft : public Command
{
public:
  CmdMoveLeft(){}
  virtual float execute(Minion &minion, Map &map)
  {
    return minion.move(MoveDir::L, map);
  }
};
class CmdMoveDown : public Command
{
public:
  CmdMoveDown(){}
  virtual float execute(Minion &minion, Map &map)
  {
    return minion.move(MoveDir::D, map);
  }
};
class CmdMoveUp : public Command
{
public:
  CmdMoveUp(){}
  virtual float execute(Minion &minion, Map &map)
  {
    return minion.move(MoveDir::U, map);
  }
};

class CmdMoveUpRight : public Command
{
public:
  CmdMoveUpRight(){}
  virtual float execute(Minion &minion, Map &map)
  {
    return minion.move(MoveDir::UR, map);
  }
};
class CmdMoveUpLeft : public Command
{
public:
  CmdMoveUpLeft(){}
  virtual float execute(Minion &minion, Map &map)
  {
    return minion.move(MoveDir::UL, map);
  }
};
class CmdMoveDownRight : public Command
{
public:
  CmdMoveDownRight(){}
  virtual float execute(Minion &minion, Map &map)
  {
    return minion.move(MoveDir::DR, map);
  }
};
class CmdMoveDownLeft : public Command
{
public:
  CmdMoveDownLeft(){}
  virtual float execute(Minion &minion, Map &map)
  {
    return minion.move(MoveDir::DR, map);
  }
};

}
