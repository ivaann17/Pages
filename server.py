from flask import Flask, request, jsonify
from flask_cors import CORS
import subprocess
import re
import os
import sys
import traceback

app = Flask(__name__)
CORS(app)

def extract_class_name(java_code):
    class_declaration_regex = r"public\s+class\s+([^\s{]+)"
    match = re.search(class_declaration_regex, java_code)
    if match:
        return match.group(1)
    else:
        return None

with open('compi.html') as html_file:
    HTML_CONTENT = html_file.read()

@app.route('/')
def index():
    return HTML_CONTENT

@app.route('/compileC', methods=['POST'])
def compile_c_code():
    return compile_code('gcc', 'C')

@app.route('/compileJ', methods=['POST'])
def compile_java_code():
    return compile_code('javac', 'Java')

@app.route('/compileCpp', methods=['POST'])
def compile_cpp_code():
    return compile_code('g++', 'Cpp')

@app.route('/compilePy', methods=['POST'])
def compile_python_code():
    return compile_code('python3', 'Py')

def compile_code(compiler, language):
    data = request.json
    code = data['code']
    file_name = f'{extract_class_name(code)}.java' if language == 'Java' else f'temp.{language.lower()}'
    
    with open(file_name, 'w') as f:
        f.write(code)
    
    try:
        if compiler in ['gcc', 'g++']:
            process = subprocess.Popen([compiler, file_name, '-o', f'temp_{extract_class_name(code)}'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            output, error = process.communicate()
            output = output.decode('utf-8')
            error = error.decode('utf-8').strip()
            if process.returncode != 0:
                return jsonify({'error': error})
            else:
                process = subprocess.Popen([f'./temp_{extract_class_name(code)}'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output, error = process.communicate()
                output = output.decode('utf-8')
                error = error.decode('utf-8').strip()
                return jsonify({'output': output, 'error': error})
        elif compiler == 'javac':
            process = subprocess.Popen([compiler, file_name], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            output, error = process.communicate()
            output = output.decode('utf-8')
            error = error.decode('utf-8').strip()
            if process.returncode != 0:
                return jsonify({'error': error})
            else:
                # Parseamos los datos de entrada separados por coma
                input_data = data.get('input_data', '').split(',')
                process = subprocess.Popen(['java', extract_class_name(code)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                output, error = process.communicate(input=bytes('\n'.join(input_data), 'utf-8'))
                output = output.decode('utf-8')
                error = error.decode('utf-8').strip()
                if process.returncode != 0:
                    return jsonify({'error': error})
                else:
                    return jsonify({'output': output})
        elif compiler == 'python3':
            process = subprocess.Popen([compiler, file_name], stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE)
            output, error = process.communicate(input=bytes(code, 'utf-8'))
            output = output.decode('utf-8')
            error = error.decode('utf-8').strip()
            if process.returncode != 0:
                traceback_msg = traceback.format_exc()
                print("Compilation Error:", error, file=sys.stderr)
                print("Traceback:", traceback_msg, file=sys.stderr)
                return jsonify({'error': error, 'traceback': traceback_msg})
            else:
                return jsonify({'output': output})
    finally:
        cleanup_files(file_name)

def cleanup_files(file_name):
    if os.path.exists(file_name):
        os.remove(file_name)

if __name__ == '__main__':
    app.run(debug=True)
