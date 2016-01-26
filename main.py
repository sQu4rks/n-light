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

@app.route("/controlle")
@require_auth
def main_controlle():
    return render_template("controle.html")

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
    source = make_response(render_template("base.ino", chars=formatted_word,used_chars=required_chars)).data

    source_str = source.decode('utf-8')

    compile_path = "/home/nlight/src"
    # Delete everything in path
    if os.path.exists(compile_path):
        shutil.rmtree(compile_path)
        os.makedirs(compile_path)
    else:
        os.makedirs(compile_path)

    with open(compile_path + "/source.ino", "w") as f:
        print("Wrinting files to " + compile_path + "source.ino")
        f.writelines(source_str)
        f.close()
    # Run compiler
    os.system("cd /home/nlight/ && ino build && ino upload")

    return redirect("/controlle")
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
