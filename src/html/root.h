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
  
          h1,
          h2 {
              color: white;
              text-align: center;
          }
  
          .btn-manual {
              color: black;
              background-color: #FFA500;
          }
  
          .btn-waypoint {
              color: black;
              background-color: #FFA500;
          }
          
          .btn-heading {
              color: black;
              background-color: #FFA500;
          }
          
          .btn-danger {
              color: white;
              background-color: #dc3545;
          }
  
          button {
              border-radius: 20px;
          }
          
          .btn {
              width: 60%;
              height: 60;
              margin: 0 auto;
              display: block;
              font-size: 30px;
              margin-top: 30px;
          }
          
          @media (min-width: 768px) {
              .btn {
                  width: 50%;
              }
          }
          
          .modus-operandi {
              text-align: center;
              font-size: 24px;
              margin-top: 20px;
          }
      </style>
  </head>
  <body>
      <div class="container-fluid">
          <div class="row">
              <div class="col-md-6 col-md-offset-3 text-center">
                  <a href="/manual" class="btn btn-manual">Manual Mode</a>
                  <a href="/settings" class="btn btn-danger">Settings</a>
              </div>
          </div>
      </div>
  </body>
</html>
)"