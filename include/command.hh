#pragma once
#include "minion.hh"

namespace ed
{

class Command
{
public:
  virtual ~Command() {};
  virtual void execute(Minion &minion) = 0;
};

class CmdMoveRight : public Command
{
public:
  virtual void execute(Minion &minion)
  {
    minion.move(MoveDir::R);
  }
};

class CmdMoveRandom : public Command
{
public:
  virtual void execute(Minion &minion)
  {
    minion.move(MoveDir::Random);
  }
};

}