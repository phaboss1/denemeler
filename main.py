from ursina import *
from player import ThirdPersonController
from ursina.prefabs.first_person_controller \
import FirstPersonController
from ursina.prefabs.health_bar import *
from animasyon import *

app = Ursina()

normalJump = 0.3
normalSpeed = 3



player = ThirdPersonController("cube", (0, 3, 0), "box")
player.jump_height = normalJump
player.SPEED = normalSpeed
player.position= Vec3(0,0.25,0)

health_bar_1 = HealthBar(bar_color=color.lime.tint(-.22), roundness=.2, value=100)




light = PointLight(parent = camera, color = color.white, position = (0, 10, -1.5))
AmbientLight(color = color.rgba(100, 100, 100, 0.1))

zemin = Entity(model = "cube", scale = (1000, 0.1, 1000), collider = "mesh" and "cube", texture = "grass", color = "#CACACA")

obje1 = Entity(model = "cube", scale = (1, 4, 1), collider ="cube"and "mesh", texture = "red", color = "#CACACA")
obje2 = Entity(model="object\\ev1",scale=1,collider="cube"and "mesh",texture="texture\\ev1.png")

obje1.position=Vec3(10,2,10)

obje2.position=Vec3(20,0,20)
obje2.rotation=Vec3(0,-90,0)


def input(key):

    if held_keys['w']:
        yurume("animation\\jetpack_walking", fps=24, loop=True, autoplay=True, frame_times=120,
               texture="texture\\char")

    if held_keys['s']:
        yurume("animation\\jetpack_waiting", fps=24, loop=True, autoplay=True, frame_times=120,
               texture="texture\\char")



def input(key):
    if key == "left mouse down":
        print("vurus")


def update():
    """if player.y <= -50:
        player.position = (0, 10, 0)
        player.SPEED = normalSpeed
        player.jump_height = normalJump

    if held_keys["g"]:
        player.position = (0, 10, 0)"""

    if held_keys['w']:
        player = yurume("animation\\jetpack_walking", fps=24, loop=True, autoplay=True, frame_times=120,
               texture="texture\\char")

































app.run()