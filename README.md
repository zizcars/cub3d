# **Cub3D: A Moroccan Hamam Adventure** 🧖‍♂️✨  

**Step into a steamy Moroccan hamam and navigate its maze-like chambers in this 3D raycaster!** Inspired by **Wolfenstein 3D**, this project transforms the classic shooter into a relaxing (or maybe not-so-relaxing?) journey through a traditional bathhouse. Will you find the exit before your *kesa* (scrubbing glove) runs out of steam?  

---

## **The Hammam Experience** 🏺  

### **1. The Layout (Parsing the Map)**  
Your `.cub` file isn’t just any map—it’s the blueprint of a **Moroccan hammam**:  
- `1` = **Hot Steam Walls** (don’t touch, they burn!)  
- `0` = **Wet Tile Floors** (slippery—move carefully!)  
- `N/S/E/W` = **Your Starting Position** (are you facing the *Mauritanian sauna* or the *Argan oil room*?)  

**Example Hammam Map:**  
```plaintext
NO ./textures/zelig1.xpm  #North walls texture
SO ./textures/zelig2.xpm
EA ./textures/zelig3.xpm
WE ./textures/zelig4.xpm

F 150,100,50   
C 50,200,255 

1 1 1 1 1 1  
1 0 0 S 0 1  
1 0 1 0 0 1  
1 0 0 0 0 1  
1 1 1 1 1 1  
```  

⚠️ **Errors?**  
- **Open walls?** Cold drafts ruin the steam! ❄️  
- **Missing textures?** No *savon beldi* (black soap)? Catastrophe! 🧼💥  

---

### **2. Raycasting Through the Steam** ☁️  
You’re not just walking—you’re **peering through the mist**, using math magic (*DDA algorithm*) to avoid bumping into hot walls.  

- **Textured walls:** Mosaic tiles, wooden doors, and piles of towels.  
- **Floor & ceiling:** Warm clay underfoot, swirling steam above.  

---

### **3. Controls (How to Not Slip & Fall)** 🕹️  
- `W`/`S` = **Step forward/back** (watch out for soap puddles!)  
- `A`/`D` = **Slide left/right** (towel around your waist?)  
- `←`/`→` = **Look around** (admire the architecture!)  
- `ESC` = **Give up** (did the heat win?)  

---

## **How to Run** 🚀  
```bash
make            # Build the magic  
./cub3D maps/hammam.cub   # Enter the steam room  
```  

---

## **Why This Project?** 🤔  
- **Learn raycasting** (so you can make games, not just play them).  
- **Master parsing** (because even hammams need rules).  
- **Survive the heat** (debugging is like a *super-hot sauna*—painful but rewarding).  

---

## **Final Wisdom** 🧠  
> *"A good hammam, like good code, is built on strong foundations. Don’t slip on the soap!"* — Ancient Moroccan Dev  

Now go forth, brave *hammam explorer*, and may your framerate stay high and your bugs stay low! 🚿🔥  

*(P.S. If you get stuck, remember: even the best steam rooms have an exit.)*