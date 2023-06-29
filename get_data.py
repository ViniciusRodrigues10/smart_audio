import serial

def get_data_usb(usb_port='COM7'):

    array_frequencies = []

    porta = serial.Serial(usb_port, 1000000)

    while True:
        
        try:

            data = porta.readline().decode().strip()

            if data == "end":
                print(f"ARRAY: {array_frequencies}")
                if len(array_frequencies) > 0:
                    return array_frequencies 

            array_frequencies.append(int(data)) 

        except UnicodeDecodeError:
            print("Foi recebido um dado com erro na codifiação")
            continue

        except ValueError:
            print("Foi recebido um dado que não pode ser convertido para int")
            continue

    porta.close()
