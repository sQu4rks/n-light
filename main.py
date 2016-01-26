#!/usr/bin/env python3
# -*- encoding: utf-8 -*-

from web.auth import *

from flask import Flask
from flask import request
from flask import render_template
from flask import make_response
from flask import redirect

import shutil
import os
from letters import Letters

app = Flask(__name__)
let = Letters()
@app.route("/")
def main():
    return render_template("home.html")

@app.route("/compile-error")
def error():
    return render_template("error.html")
@app.route("/controlle")
@require_auth
def main_controlle():
    return render_template("controle.html")

@app.route("/send-template",methods=['POST'])
@require_auth
def send_template():
    template = request.form['program']
    source = make_response(render_template(template)).data
    source_str = source.decode('utf-8')

    ret = compile_avr(source_str)

    if ret == "ERR":
        return redirect("/compile-error")
    return redirect("/controlle")
@app.route("/send-char",methods=['POST'])
@require_auth
def send_char():
    name = request.form['char_n']
    vals = []
    for x in range(0,7):
        for y in range(0,7):
            elem_id = "check-" + str(x) + "-" + str(y)
            if request.form.get(elem_id,'false') == "on":
                vals.append('true')
            else:
                vals.append('false')
    chardecode = "Character char" + name + "{7, {" + ",".join(vals) + "}};"
    let.add_letter(name, chardecode)
    return redirect("/controlle")
@app.route("/send-text",methods=['POST'])
@require_auth
def send_text():
    word = request.form['text']
    individuals = find_individuals(word)
    formatted_word = []
    for w in word:
        formatted_word.append("&" + get_word_equivalent(w))
    required_chars = []
    for c in individuals:
        required_chars.append(let.get_letter(c))
    source = make_response(render_template("base.ino", chars=formatted_word,used_chars=required_chars,speed=request.form['speed'],color=request.form['color'])).data

    source_str = source.decode('utf-8')
    ret = compile_avr(source_str)

    if ret == "ERR":
        return redirect("/compile-error")
    return redirect("/controlle")

def compile_avr(source_str,compile_path = "/home/nlight/src"):
    if os.path.isfile("/home/nlight/compile.lock"):
        return "ERR"
    else:
        with open("/home/nlight/compile.lock","w") as l:
            l.write("Locked")
            l.close()
        # Delete everything in path
        if os.path.exists(compile_path):
            shutil.rmtree(compile_path)
            os.makedirs(compile_path)
        else:
            os.makedirs(compile_path)

        with open(compile_path + "/source.ino", "w") as f:
            print("Writing files to " + compile_path + "/source.ino")
            f.writelines(source_str)
            f.close()
        # Run compiler
        os.system("cd /home/nlight/ && ino build && ino upload")
        # Remove compile log
        os.remove("/home/nlight/compile.lock")
        return "OK"
def find_individuals(text):
    individuals = []
    for s in text:
        if s in individuals:
            pass
        else:
            individuals.append(s)
    return individuals

def get_word_equivalent(w):
    if w == " ":
        return "char" + str("Sp")
    else:
        return "char"+ str(w).upper()
if __name__ == "__main__":
    app.run(debug=True,host='0.0.0.0')
