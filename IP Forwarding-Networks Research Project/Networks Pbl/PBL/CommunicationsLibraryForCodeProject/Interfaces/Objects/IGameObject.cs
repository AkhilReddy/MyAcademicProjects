using System.ComponentModel;
using System.Collections.Generic;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IGameObject : IHasClassTypeName, IHasCategory, IHasType, IHasSize, IHasWeight, IFromTemplate<IGameObjectTemplate>, IHasTemplateID 
   {
      long ObjectID { get; set; }      
      long CarriedByEntityID { get; set; }
      long InObjectID { get; set; }
      ILocation AtLocation { get; set; }
   }
}
