import streamlit as st
import webbrowser
import requests
import matplotlib.pyplot as plt

from pages import patient

with open("style.css") as f:
    st.markdown('<style>{}</style>'.format(f.read()), unsafe_allow_html=True)

def cmToPercent(cm):
    return (cm/17)*100


st.title("Nurse Dashboard", anchor="center")    

# blank space
st.write("")
st.write("")
st.write("")
st.write("")


# horizontal view

col1a,col1b,col1c = st.columns(3)

with col1a:
    st.image("./images/1.png", width=200 , use_column_width=True)
    
    
    st.markdown("Dashboard to view volume , rate , etc for patients drips")




with col1b:
    st.image("./images/2.png", width=200, use_column_width=True)
    st.markdown("Option to Refill fulid bag online")

with col1c:
    st.image("./images/3.png", width=200, use_column_width=True)
    st.markdown("Panic button for patient to call nurse")



# blank space
st.write("")
st.write("")
st.write("")
st.write("")

col2a,col2b,col2c = st.columns(3)

with col2a:
    # request to http://192.168.131.201:8001/getdata
    response = requests.get("http://192.168.43.201:8001/getdata")
    # the response is of type [{'timestamp': '21:38:20', 'cm': 16.24, 'inches': 6.39}]
    volume = (100-cmToPercent(response.json()[0]['cm'])).__round__(2)
    # square  box
    st.markdown(f'<div class="square blue"><center> <h3>309</h3> Rate:100 </br> Volume : {volume}% </br> Fluid : B Complex  </center> </br></br></div>', unsafe_allow_html=True)
    # if volume is in percentage make it pie chart
    if volume < 100:
        fig, ax = plt.subplots()
        ax.pie([volume, 100-volume], labels=["Volume", "Empty"], autopct='%1.1f%%', shadow=True, startangle=90)
        st.pyplot(fig)
    


    # when button is clicked print the key
    if st.button("Explore", key="309"):
        webbrowser.open_new_tab("http://localhost:8501/patient")
        st.write("309")

            






with col2b:
    # square  box
    st.markdown('<div class="square red"><center> <h3>310</h3> Rate:100 </br> Volume : 7500 </br> Fluid : B Complex  </center> </br></br></div>', unsafe_allow_html=True)
    if st.button("Explore", key="310"):
        st.write("310")

with col2c:
    # square  box
    st.markdown('<div class="square blue"><center> <h3>311</h3> Rate:100 </br> Volume : 7500 </br> Fluid : B Complex  </center></br></br> </div>', unsafe_allow_html=True)
    if st.button("Explore", key="311"):
        st.write("311")
