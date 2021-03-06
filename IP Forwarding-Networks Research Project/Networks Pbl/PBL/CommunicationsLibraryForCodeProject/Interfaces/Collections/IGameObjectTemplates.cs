﻿using System.ComponentModel;
using System.Collections.Generic;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IGameObjectTemplates : ISupportsRemove<IGameObjectTemplate>, ISupportsAdd<IGameObjectTemplate>, IMultipleItems<IGameObjectTemplate>,
      ISupportsFind<long, IGameObjectTemplate>
   {
      IObjectTemplateCollection FindObjectTemplatesByCategory(int category);
      IObjectTemplateCollection FindObjectTemplatesByType(int type);      
   }
}
