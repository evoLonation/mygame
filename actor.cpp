//#include"actor.h"
//Actor::Actor(Model* model): model(model), worldTransUpdate(false){}
//void Actor::setScale(float scale){
//   this->scale = Matrix4::CreateScale(scale);
//   computeWorldTrans();
//}
//void Actor::RotateZ(float theta){
//   rotation *= Matrix4::CreateRotationZ(theta);
//   computeWorldTrans();
//}
//void Actor::RotateY(float theta){
//   rotation *= Matrix4::CreateRotationY(theta);
//   computeWorldTrans();
//}
//void Actor::RotateX(float theta){
//   rotation *= Matrix4::CreateRotationX(theta);
//   computeWorldTrans();
//}
//Matrix4* Actor::getWorldTrans(){
//   return &worldTransMatrix;
//}
//void Actor::computeWorldTrans(){
//   // worldTransMatrix = Matrix4();
//   // worldTransMatrix = scale;
//   worldTransMatrix *= rotation;
//   worldTransMatrix *= translation;
//}