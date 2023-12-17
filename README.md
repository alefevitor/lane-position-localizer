<div align="center">
<h1> Lane Position Localizer: Precise Localization on the Runway Using Lane Detection 🚗 </h1>

<!-- <--!span><font size="5", > Efficient and Robust 2D-to-BEV Representation Learning via Geometry-guided Kernel Transformer
</font></span> -->

  Alefe Gadioli e Israel Barbosa
<!-- <a href="https://scholar.google.com/citations?user=pCY-bikAAAAJ&hl=zh-CN">Jinwei Yuan</a> -->
<div><a href="https://drive.google.com/file/d/15c9RdFCcthiwg9AKDCs5SAQKj0-J2LT6/view?usp=sharing">Lane Position Localizer Report</a></div> 

</div>

# Introduction

Autonomous driving is a groundbreaking technology that is reshaping the transportation industry, offering the potential to greatly enhance road safety and increase the efficiency of mobility. Autonomous vehicles offer a multitude of advantages, including accident prevention, optimized fuel consumption, and improved passenger comfort. In this swiftly evolving field, probabilistic mathematical models play a pivotal role in addressing the challenges posed by uncertainty, particularly in achieving precise vehicle localization and accurate detection of traffic lanes.

## Localization Approaches
In the realm of autonomous driving, several approaches have been employed to address the crucial task of precise localization. Methods such as the Extended Kalman Filter, Particle Filter, and Probabilistic Occupancy Map are widely utilized to estimate the vehicle's position relative to its surrounding environment.

## Proposed Model
Our proposed model leverages the YOLOPv2 neural network for real-time detection of traffic lanes and vehicles. This system integrates color information for lane detection and utilizes a pretrained neural network for vehicle identification. The data captured by this model is subsequently employed for the navigation of the autonomous vehicle, while accounting for the inherent uncertainty present in the environment.

In this approach, we replace the conventional use of LiDAR with GPS, employing a measurement model that considers both camera and GPS data. This ensures an accurate estimation of the vehicle's pose in Frenét coordinates.

<div align="center">
  <a href="https://ibb.co/1bjc38J"><img src="https://i.ibb.co/jHstdgZ/Screenshot-from-2023-12-16-21-54-57.png" alt="Screenshot-from-2023-12-16-21-54-57" border="0"></a>
</div>

## Implementation Methodology

The practical implementation of our method has been executed on a physical vehicle equipped with a camera and a GPS system. Although practical trials have not yet been conducted, our approach enables real-time detection using the YOLOPv2 network, enabling a continuous and precise update of the vehicle's position based on sensor data. We have chosen to integrate our method with the CARMEN system, facilitating seamless integration with other modules of the autonomous vehicle, such as trajectory planning and motion control. This integration enables safe operation in complex environments and efficient code reuse in future projects, contributing to the ongoing advancement of autonomous driving and vehicle localization.

## Results
The results of using the detection module have shown promise with the utilization of the YOLOPv2 convolutional neural network, as can be seen in the following figures.

### Visualization
<div align="center">
  <td><img src=https://i.ibb.co/44x03D9/Design-sem-nome.png></td>
  <p> Detection of representative lanes and navigable areas - UFES Loop </p>
</div>

<div align="center">
  <td><img src=YOLOPv2/data/video2.gif></td>
  <p> Detection of representative lanes and navigable areas - LUME</p>
</div>

However, it is evident that the model faces challenges in detecting areas where lane markings are not clear, as illustrated in Figure 1. Conversely, the detection improves significantly in sharper areas, as demonstrated in Figure 2.



# Installation
## 1. Prerequisites

- Python 3.6 or higher
- IP Webcam with RTSP enabled

## 2. Environment Setup
### 1. Install Python 3.6 or higher:
- **Windows:** Download the installer from <a href="https://www.python.org/downloads/">the official Python website</a>
- **Linux:** Use your distribution's package manager, for example:
``` shell
# Python3 - Linux
sudo apt-get install python3
```

### 2. Clone the Repository:
- Open a terminal
``` shell
# ai-want-coffee
git clone https://github.com/lewislf/ai-want-coffee.git
```

### 3. Install Dependencies:
- Open a terminal and navigate to the cloned project directory.
 ``` shell
# Open the Folder
cd ai-want-coffee
```
-  Install all required dependencies
``` shell
# ai-want-coffee
pip install -r requirements.txt
```

## 3. Project Configuration
- Obtain an API Key from OpenAI by creating an account at <a href="https://openai.com/">OpenAI</a>.
- Open the file named api_key.py in the project directory and define OPENAI_API_KEY with your key and Replace the ip and port in the ip_address variable with your IP webcam's information, in the LOCAL_CAMERA variable.
``` shell
# api_key.py
OPENAI_API_KEY = 'YOUR API KEY'
LOCAL_CAMERA = "rtsp://ip:port/h264_ulaw.sdp" 
```

## 4. Execution
### 1. Run the Script:
- Open de folder **predict**:
 ```shell
# ai-want-coffee/predict/
cd ai-want-coffee/predict/
```
- In the terminal, execute python gpt.py
```shell
# Navigate to the ai-want-coffee repository and execute the following:
python3 gpt.py
```


# Future Works
Explore how to eliminate the "interact" function that was made available to the Coffee-Agent, since it is classified as an abstract order. Works that are outside the scope of the AGI subject, but continue from what was produced: Improve integration with Coffee-Assistant through the voice communication module we developed. Use it for tasks other than making coffee. Integration with VR glasses.
