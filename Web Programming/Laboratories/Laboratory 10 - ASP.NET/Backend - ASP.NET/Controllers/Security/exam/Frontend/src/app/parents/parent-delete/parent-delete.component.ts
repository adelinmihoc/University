import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {ParentService} from "../shared/parent.service";

@Component({
  selector: 'app-parent-delete',
  templateUrl: './parent-delete.component.html',
  styleUrls: ['./parent-delete.component.css']
})
export class ParentDeleteComponent implements OnInit {
  parentDeleteForm = new FormGroup({
    id: new FormControl('', [
      Validators.required,
      Validators.pattern('^[0-9]*$')
    ])
  });

  constructor(private parentService: ParentService) { }

  ngOnInit(): void {
  }

  onSubmitDeleteById(form: FormGroup) {
    if (form.valid) {
      this.parentService.delete(form.value.id);
    } else {
      alert("please enter a valid id");
    }
  }

  get id() {
    return this.parentDeleteForm.get('id');
  }

}
