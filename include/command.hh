#pragma once
#include "minion.hh"
#include "map.hh"

namespace ed
{

enum class CmdType
{
  None,
  MinionMoveRight,
  MinionMoveRandom
};

class Command
{
public:
  Command(CmdType type)
    : type_{type}
  {
    //
  }
  virtual ~Command() {};
  virtual void execute(Minion &minion, Map &map) = 0;
};

class CmdMoveRight : public Command
{
public:
  CmdMoveRight()
    : Command{CmdType::MinionMoveRight}
  {
    //
  }
  virtual void execute(Minion &minion, Map &map)
  {
    minion.move(MoveDir::R, map);
  }
};

class CmdMoveRandom : public Command
{
public:
  CmdMoveRandom()
    : Command{CmdType::MinionMoveRandom}
  {
    //
  }
  virtual void execute(Minion &minion, Map &map)
  {
    minion.move(MoveDir::Random, map);
  }

};

}
