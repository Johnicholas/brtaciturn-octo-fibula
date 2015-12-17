using UnityEngine;
using System;
using System.Runtime.InteropServices;

class Viva : MonoBehaviour {

  public delegate void newSprite(int spriteId, int x, int y, int texture, int layer);
  public delegate void freeSprite(int spriteId);
  public delegate void setSpritePosition(int spriteId, int x, int y);
  public delegate void setSpriteTint(int spriteId, int color);
  public delegate void setSpriteRotation(int spriteId, float rotation);
  public delegate void setCount(int which, int newValue);
  public delegate void setMuted(int newValue);

  // Please call this first, before any other method.
  [DllImport ("DLLImport_CProj")]
  private static extern void begin(
    newSprite a,
    freeSprite b,
    setSpritePosition c,
    setSpriteTint d,
    setSpriteRotation e,
    setCount f,
    setMuted g
  );

  // Please call this frequently, maybe 60 times per second.
  [DllImport ("DLLImport_CProj")]
  private static extern void update();

  // Please call this when the user presses a mouse button.
  [DllImport ("DLLImport_CProj")]
  private static extern void mouse_down(int x, int y);

  // Please call this when the user releases a mouse button.
  [DllImport ("DLLImport_CProj")]
  private static extern void mouse_up(int x, int y);

  // Please call this when the user's mouse arrives and/or becomes relevant.
  [DllImport ("DLLImport_CProj")]
  private static extern void mouse_over(int x, int y);

  // Please call this when the user's mouse leaves and/or becomes irrelevant.
  [DllImport ("DLLImport_CProj")]
  private static extern void mouse_out();

  // Please call this whenever the user moves the mouse (within this scene).
  [DllImport ("DLLImport_CProj")]
  private static extern void mouse_move(int x, int y);

  void Awake() {
    begin(
      new newSprite( this.newSpriteCallback ),
      new freeSprite( this.freeSpriteCallback ),
      new setSpritePosition( this.setSpritePositionCallback ),
      new setSpriteTint( this.setSpriteTintCallback ),
      new setSpriteRotation( this.setSpriteRotationCallback ),
      new setCount( this.setCountCallback ),
      new setMuted( this.setMutedCallback )
    );
  }

  void newSpriteCallback(int spriteId, int x, int y, int texture, int layer) {
    // TODO: Ceu is telling Unity to create a new sprite, named "spriteId".
  }

  void freeSpriteCallback(int spriteId) {
    // TODO: Ceu is telling Unity to delete the (previously-created) sprite spriteId
  }

  void setSpritePositionCallback(int spriteId, int x, int y) {
    // TODO: Ceu is telling Unity to move the previously-created sprite spriteId to x, y
  }

  void setSpriteTintCallback(int spriteId, int newColor) {
    // TODO: Ceu is telling Unity to tint the (previously-created) sprite spriteId a new color
  }

  void setSpriteRotationCallback(int spriteId, float rotation) {
    // TODO: Ceu is telling Unity that the (previously-created) sprite spriteId should be rotated 
    // a specific number of radians
  }

  void setCountCallback(int which, int newValue) {
    // TODO: Ceu is telling Unity that the count of "which" (a number in the UI) is now newValue
  }

  void setMutedCallback(int newValue) {
    // TODO: Ceu is telling Unity to mute sound (if newValue == 1) or to unmute it (if newValue == 0)
  }

}
