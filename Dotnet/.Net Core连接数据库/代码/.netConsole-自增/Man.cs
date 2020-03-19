
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.IO;
using System.Linq;
using System.Text;

namespace ConsoleApp2.Model
{
    [Table("Man")]
    public class Man
    {
        [Key]
        [DatabaseGenerated(System.ComponentModel.DataAnnotations.Schema.DatabaseGeneratedOption.Identity)]//添加时自动增长
        public int uid { get; set; }
       
        public string name { get; set; }
        //public int age { get; set; }
        //public string sex { get; set; }
    }
}