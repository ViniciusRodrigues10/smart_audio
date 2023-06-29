import tkinter as tk
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import get_data

RATE = 44100
USB_PORT= 'COM7'

# Frequências para as barras
bar_frequencies = [80, 200, 315, 400, 500, 630, 800, 1000, 1250, 1600, 2000, 2500, 3150, 4000, 5000, 6300, 8000, 10000, 12500, 16000, 20000]

# Função para encontrar o índice da frequência mais próxima
def find_nearest_frequency_index(frequency, frequencies):
    return np.abs(frequencies - frequency).argmin()

# Função para atualizar o espectro'
def update_spectrum():
    y_min = 0 
    y_max = 120000

    # Salva os dados enviados pelo STM32 na variável data
    data = np.array(get_data.get_data_usb(USB_PORT)) 
    # Realiza a transformada de Fourier
    spectrum = np.fft.fft(data) 
    frequencies = np.fft.fftfreq(len(data), 1.0/RATE)
    spectrum = np.abs(spectrum)
    #print(frequencies)

    bar_indices = [find_nearest_frequency_index(freq, frequencies) for freq in bar_frequencies]

    canvas.figure.clear()
    ax = canvas.figure.add_subplot(111)
    bars = ax.bar(np.arange(len(bar_frequencies)), spectrum[bar_indices], width=0.8, align='center', edgecolor='black')
    ax.set_xlabel('Frequência (Hz)', fontsize=12)
    ax.set_ylabel('Amplitude', fontsize=12)
    ax.set_title('Analisador de Espectro de Áudio', fontsize=14)
    ax.set_xticks(np.arange(len(bar_frequencies)))
    ax.set_xticklabels(bar_frequencies, rotation=0)
    # Ajuste dos limites do eixo x
    ax.set_xlim(-0.5, len(bar_frequencies) - 0.5) 
     # Ajuste dos limites do eixo y 
    ax.set_ylim(y_min, y_max) 
    
    # Ajusta as cores das barras
    for bar in bars:
        bar.set_color('steelblue')
    
    canvas.draw()

    root.after(50, update_spectrum)

# Configuração do Tkinter
root = tk.Tk()
root.title("Analisador de Espectro de Áudio")

# Configuração da figura do Matplotlib
figure = plt.Figure(figsize=(8, 4.5), dpi=100)
canvas = FigureCanvasTkAgg(figure, master=root)
canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
canvas.figure.tight_layout()

# Inicia a atualização do espectro
update_spectrum()

# Executa o loop principal do Tkinter
root.mainloop()
