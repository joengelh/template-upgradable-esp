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
        .container {
    display: flex;
    justify-content: center;
  }
  
  /* Style the box */
  .box {
    width: 300px;
    background-color: #303030;
    border: 1px solid gray;
    text-align: center;
    line-height: 50px;
  }
    /* Header styles */
    header {
      background-color: #303030;
      padding: 10px;
      display: flex;
      justify-content: space-between;
      align-items: center;
      margin-bottom: 10px; /* add margin-bottom */
    }

    #home-button {
      color: white;
      font-size: 18px;
      text-decoration: none;
    }

    #home-button:hover {
      text-decoration: underline;
    }

    #form-container {
      display: flex;
      justify-content: center;
      align-items: center;
      margin-top: 5px; /* Adjust this value as needed */
      padding: 5px 10px; /* Adjust the padding to resize the button */
      font-size: 14px; /* Adjust the font size to resize the button text */
    }
    
    #form {
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
      padding: 1rem;
      border: 1px solid black;
      border-radius: 5px;
      box-shadow: 2px 2px 5px grey;
      margin: 0 auto; /* center the form */
      margin-top: 1rem; /* Add or adjust the top margin */
    }

    #calibrate {
      margin: 0.5rem;
      padding: 0.5rem;
      font-size: 1rem;
      border-radius: 5px;
      border: none;
      background-color: #dc3545;
      color: white;
      width: 8rem;
      cursor: pointer;
      transition: background-color 0.2s ease-in-out;
      margin-top: 10px; /* Adjust this value as needed */
    }

    #submit {
      margin: 0.5rem;
      padding: 0.5rem;
      font-size: 1rem;
      border-radius: 5px;
      border: none;
      background-color: #39FF14;
      color: white;
      width: 8rem;
      cursor: pointer;
      transition: background-color 0.2s ease-in-out;
    }

    #submit:focus {
      outline: none;
    }

    #submit:hover {
      background-color: #39FF14;
    }

    body {
      background-color: #303030;
      color: white;
      margin: 0; /* remove default body margin */
    }
    .newFactor-form {
    margin-top: 1rem;
    }
    
    .newFactor-form label {
      margin-bottom: 0.5rem;
    }
    
    .newFactor-form input[type="number"] {
      width: 100%;
      padding: 0.5rem;
      border-radius: 5px;
      border: 1px solid #ccc;
      font-size: 1rem;
      margin-bottom: 0.5rem;
    }
  </style>
</head>
<body>
  <div class="container">
    <div class="box">
      <h3>Update Firmware</h3>
      <form method="POST" action="#" enctype="multipart/form-data" id="upload_form">
        <input type="file" name="update">
        <input type="submit" value="Update">
      </form>
      <div id="prg">progress: 0%</div>
    </div>
  </div>
  <script>
    function makePost(endpoint, data) {
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          // handle the response
          console.log(this.responseText);
        }
      };
      var url = window.location.origin + '/' + endpoint;
      xhr.open("POST", url, true);
      xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
      var encodedData = Object.keys(data)
        .map(function (key) {
          return encodeURIComponent(key) + "=" + encodeURIComponent(data[key]);
        })
        .join("&");
      xhr.send(encodedData);
    }
  </script>
  <script>
    function uploadFirmware() {
      var form = document.getElementById("upload_form");
      var fileInput = document.querySelector('input[type="file"]');
      var progressBar = document.getElementById("prg");

      var xhr = new XMLHttpRequest();
      xhr.open("POST", "/update");

      xhr.upload.addEventListener("progress", function (evt) {
        if (evt.lengthComputable) {
          var progress = (evt.loaded / evt.total) * 100;
          progressBar.innerHTML = "progress: " + Math.round(progress) + "%";
        }
      }, false);

      xhr.onreadystatechange = function () {
        if (xhr.readyState === 4) {
          if (xhr.status === 200) {
            alert("Firmware upload successful!");
          } else {
            alert("Firmware upload failed.");
          }
        }
      };

      var formData = new FormData(form);
      formData.append("update", fileInput.files[0]);

      xhr.send(formData);
    }

    document.addEventListener("DOMContentLoaded", function () {
      var form = document.getElementById("upload_form");
      form.addEventListener("submit", function (e) {
        e.preventDefault();
        uploadFirmware();
      });
    });
  </script>
</body>

</html>
)"