from flask import Flask, request, jsonify
from flask_cors import CORS
import subprocess
import gzip
from flask_compress import Compress

app = Flask(__name__)
CORS(app)
Compress(app)

@app.route('/')
def index():
    return open('index.html').read()

@app.route('/compile', methods=['POST'])
def compile_code():
    data = request.json
    code = data['code']
    with open('temp.c', 'w') as f:
        f.write(code)
    
    # Compilar y ejecutar el código, capturando la salida
    result = subprocess.run(['emcc', 'temp.c', '-o', 'temp.js', '-s', 'EXIT_RUNTIME=1'], capture_output=True, text=True)
    if result.returncode == 0:
        try:
            output = subprocess.check_output(['node', 'temp.js'], text=True)
            return jsonify({'output': output})
        except subprocess.CalledProcessError as e:
            return jsonify({'error': str(e)})
    else:
        return jsonify({'error': result.stderr})

if __name__ == '__main__':
    app.run(debug=False)  # Desactiva el modo debug y usa Gunicorn en su lugar
