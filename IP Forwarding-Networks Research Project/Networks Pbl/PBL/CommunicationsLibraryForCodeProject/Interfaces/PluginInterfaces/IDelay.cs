using System;
using System.Collections.Generic;
using System.Text;


namespace EmlenMud.Interfaces
{
   public interface IPersistsWorld
   {
      CreatePersistentEntityDelegate CreatePersistentEntity { get; set; }
      CreatePersistentEntityAbilityDelegate CreatePersistentAbility { get; set; }
      CreatePersistentParameterDelegate CreatePersistentParameter { get; set; }      
   }
}
