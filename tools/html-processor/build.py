import os

src_directory = "html/"
target_directory = "../../src/html/"
header_file = "header.html"
footer_file = "footer.html"

# Read the content of the header file
header_path = os.path.join(src_directory, header_file)
with open(header_path, "r") as header:
    header_content = header.read()

# Read the content of the footer file
footer_path = os.path.join(src_directory, footer_file)
with open(footer_path, "r") as footer:
    footer_content = footer.read()

# Iterate over files in the src directory
for file_name in os.listdir(src_directory):
    file_path = os.path.join(src_directory, file_name)

    if file_name != header_file and file_name != footer_file and file_name.endswith(".html"):
        # Read the content of the current file
        with open(file_path, "r") as file:
            file_content = file.read()

        # Concatenate header, file content, and footer
        new_content = f'R"(\n{header_content}\n{file_content}\n{footer_content}\n)"'

        # Create the new file name
        new_file_name = os.path.splitext(file_name)[0] + ".h"
        new_file_path = os.path.join(target_directory, new_file_name)

        # Write the concatenated content to the new file
        with open(new_file_path, "w") as new_file:
            new_file.write(new_content)

        print(f"Created {new_file_name}")
