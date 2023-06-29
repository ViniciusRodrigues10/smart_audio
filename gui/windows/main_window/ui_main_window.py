# Import QT CORE
from qt_core import *

class UI_MainWindow(object):
    def setup_ui(self, parent):
        if not parent.objectName():
            parent.setObjectName("MainWindow")

        # Set parametros iniciais
        parent.resize(1200, 720)
        parent.setMinimumSize(960, 540)

        # Criando o widget central
        self.central_frame = QFrame()
        self.central_frame.setStyleSheet("background-color: #282a36")

        # Setando widget central
        parent.setCentralWidget(self.central_frame)