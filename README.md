Github link: https://github.com/RobbeMahieu/Prog4_Mahieu_Robbe_Pengo

This Repository contains a functional 2D game engine, together with the arcade classic Pengo that shows of the engine's capabilities.

Some design choices:
- GameObject are owned by their parent, same goes for components
- The scene is a glorified gameObject
- Subjects are the only member variables that can be public
- The elapsed frame time is stored in a singleton GameTime class
- Input devices are abstracted away behind a common interface