import streamlit as st

with open("style.css") as f:
    st.markdown('<style>{}</style>'.format(f.read()), unsafe_allow_html=True)


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
    # square  box
    st.markdown('<div class="square blue"><center> <h3>309</h3> Rate:100 </br> Volume : 7500 </br> Fluid : B Complex  </center> </br></br></div>', unsafe_allow_html=True)
    st.button("Explore", key="309")



with col2b:
    # square  box
    st.markdown('<div class="square red"><center> <h3>310</h3> Rate:100 </br> Volume : 7500 </br> Fluid : B Complex  </center> </br></br></div>', unsafe_allow_html=True)
    st.button("Explore", key="310")
with col2c:
    # square  box
    st.markdown('<div class="square blue"><center> <h3>311</h3> Rate:100 </br> Volume : 7500 </br> Fluid : B Complex  </center></br></br> </div>', unsafe_allow_html=True)
    st.button("Explore", key="311")