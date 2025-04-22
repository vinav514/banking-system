# Use an official GCC image
FROM gcc:latest

# Create and set working directory
WORKDIR /app

# Copy all source files into the container
COPY . .

# Compile your C++ code (replace Bank_Management_System.cpp with your actual file name)
RUN g++ -o banking-app Bank_Management_System.cpp

# Expose the port the application will run on (for example, 8080)
EXPOSE 8080

# Set default command to run the compiled app
CMD ["./banking-app"]
