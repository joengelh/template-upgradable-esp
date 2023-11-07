R"(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <title>ESP Template</title>
    <style>
      /* Header styles */
      header {
        background-color: #303030;
        padding: 10px;
        display: flex;
        justify-content: space-between;
        align-items: center;
      }

      #remote-text {
        color: white;
        font-size: 28px;
        margin-left: 20px;
      }

      #home-button {
        color: white;
        font-size: 20px;
        padding: 8px 8px;
        text-decoration: none;
        margin-right: 40px;
      }

      #home-button:hover {
        text-decoration: underline;
      }

      /* Unique class for the standby button in the header file */
      .btn-standby-header {
        color: white;
        background-color: #106f0a;
        border: none;
        border-radius: 40px;
        padding: 8px 16px;
        font-size: 16px;
        cursor: pointer;
      }

      .btn-standby-header:hover {
        background-color: #0a8a14;
      }
    </style>
  </head>
  <body>
    <header>
      <div id="remote-text">Remote</div>
      <div>
        <button class="btn-standby-header" onclick='makePost("standby", {"mode": "Standby"});'>Standby</button>
        <a href="/" id="home-button">Home</a>
      </div>
    </header>

    <script>
      function makePost(endpoint, data) {
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            // handle the response
            console.log(this.responseText);
          }
        };
        var url = window.location.origin + '/' + endpoint;
        xhr.open("POST", url, true);
        xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
        var encodedData = Object.keys(data).map(function(key) {
          return encodeURIComponent(key) + "=" + encodeURIComponent(data[key]);
        }).join("&");
        xhr.send(encodedData);
      }
    </script>
  </body>
</html>
<head>
  <meta charset="UTF-8">
    <style>
      body {
        font-family: Arial, sans-serif;
        color: white;
        background-color: #303030;
      }
      h1, h2, h3 {
        color: white;
        text-align: center;
      }
      .btn-default {
        color: black;
        background-color: white;
      }
      .btn-primary {
        color: white;
        background-color: #007bff;
      }
      .btn-danger {
        color: white;
        background-color: #dc3545;
      }
      button {
        border-radius: 10px;
      }
      #forwards {
        background-color: green;
        color: white;
      }
      #reverse {
        background-color: green;
        color: white;
      }
      #stop {
        background-color: red;
        color: white;
      }
    </style>
  </head>
  <head>
	<title>Boat Control</title>
    <script>
    function makePost(endpoint, data) {
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          // handle the response
          console.log(this.responseText);
        }
      };
      var url = window.location.origin + '/' + endpoint;
      xhr.open("POST", url, true);
      xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
      var encodedData = Object.keys(data).map(function(key) {
        return encodeURIComponent(key) + "=" + encodeURIComponent(data[key]);
      }).join("&");
      xhr.send(encodedData);
    }
    </script>
    <script>
      document.addEventListener("keydown", function(event) {
        var key = event.key.toLowerCase();
        if (key === "w") {
          makePost("motor", {"motor": "forwards"});
        } else if (key === "s") {
          makePost("motor", {"motor": "reverse"});
        } else if (key === "a") {
          makePost("servo", {"direction": "left"});
        } else if (key === "d") {
          makePost("servo", {"direction": "right"});
        }
      });

      document.addEventListener("keyup", function(event) {
        var key = event.key.toLowerCase();
        if (key === "w" || key === "s") {
          makePost("motor", {"motor": "stop"});
        }
        else if (key === "a" || key === "d") {
          makePost("servo", {"direction": "center"});
        }
      });
    </script>
  <body>
    <h1>Manual Control</h1>
    <h3>Use the "WASD" keys or buttons below</h3>
    <div class="container-fluid">
    <div class="col-xs-12" style="height: 25vh">
        <div class="row" style="height: 33%; padding-top: 1em; padding-bottom: 1em">
            <div class="col-xs-4" style="height: 300%; text-align: center">
                <button id="forwards" type="button" class="btn btn-default" style="height: 100%; width: 75%" onclick='makePost("motor", {"motor": "forwards"})'>Forwards</button>
            </div>
            <div class="col-xs-4" style="height: 300%; text-align: center">
                <button id="reverse" type="button" class="btn btn-default" style="height: 100%; width: 75%" onclick='makePost("motor", {"motor": "reverse"})'>Reverse</button>
            </div>
            <div class="col-xs-4" style="height: 300%; text-align: center">
              <button id="stop" type="button" class="btn btn-default" style="height: 100%; width: 75%" onclick='makePost("motor", {"motor": "stop"})'>Stop</button>
            </div>
          </div>
        </div>
    </div>
    </body>
</html>
)"