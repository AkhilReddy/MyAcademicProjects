﻿using System.ComponentModel;
using System.Collections.Generic;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IOwnsObjects 
   {
      IObjectCollection ObjectsOwned { get; }
      bool AddObject(IGameObject gameObj);
      bool RemoveObject(long objectID);
      List<IGameObject> OwnedObjectList { get; }
   }
}
