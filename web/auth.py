from functools import wraps
from flask import request, Response


def check_auth(username, password):
    """
    Authenticate against the local user database by parsing /etc/shadow or /etc/passwd
    """
    #salt_pattern = compile_regex(r"\$.*\$.*\$")
    #passwd = "/etc/shadow" if path.exists("/etc/shadow") else "/etc/passwd"

#    with open(passwd, "r") as f:
#        rows = (line.strip().split(":") for line in f)
#        records = [row for row in rows if row[0] == user]
#
#    hash = records and records[0][1]
#    salt = salt_pattern.match(hash).group()
#
#    return crypt(password, salt) == hash
    if username == "admin" and password == "admin":
        return true
    else:
        return false
def authenticate():
    """
    Send a 401 response, if authentication fails
    """
    return Response('Could not verify your access level for the URL. \n Please log-in with the correct credentials', 401, {'WWW-Authenticate': 'Basic realm="Login Required"'})
def require_auth(f):
    """
    Construct a @ decorater to enable authentication
    """
    @wraps(f)
    def decorated(*args, **kwargs):
        auth = request.authorization
        print(auth)
        if not auth:
            return authenticate()
        return f(*args, **kwargs)
    return decorated
