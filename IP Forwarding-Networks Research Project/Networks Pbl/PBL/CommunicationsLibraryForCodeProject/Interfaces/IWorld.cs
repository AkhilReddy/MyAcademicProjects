﻿using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IWorld : IMapIDToControlReceiver 
   {
      IAllEntities Entities { get; }
      IEntityLocations EntityLocations { get; }
      IAbilityTemplates AbilityTemplates { get; }
      ITypeLookup TypeProvider { get; set; }
      ITerrains Terrains { get; }
      IGameObjects GameObjects { get; }
      IGameObjectTemplates GameObjectTemplates { get; }      
   }
}
