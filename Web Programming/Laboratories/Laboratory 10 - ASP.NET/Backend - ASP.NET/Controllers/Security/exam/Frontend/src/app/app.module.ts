import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import {AppRoutingModule} from "./app-routing.module";
import {MatToolbarModule} from "@angular/material/toolbar";
import {RouterModule} from "@angular/router";
import {MatSelectModule} from "@angular/material/select";
import {MatPaginatorModule} from "@angular/material/paginator";
import {MatIconModule} from "@angular/material/icon";
import {MatInputModule} from "@angular/material/input";
import {FormsModule, ReactiveFormsModule} from "@angular/forms";
import {MatChipsModule} from "@angular/material/chips";
import {MatMenuModule} from "@angular/material/menu";
import {MatSortModule} from "@angular/material/sort";
import {MatCheckboxModule} from "@angular/material/checkbox";
import {MatTableModule} from "@angular/material/table";
import {HttpClientModule} from "@angular/common/http";
import {MatButtonModule} from "@angular/material/button";
import { ParentsComponent } from './parents/parents.component';
import { ParentListComponent } from './parents/parent-list/parent-list.component';
import { ParentAddComponent } from './parents/parent-add/parent-add.component';
import { ParentDeleteComponent } from './parents/parent-delete/parent-delete.component';
import { ParentUpdateComponent } from './parents/parent-update/parent-update.component';
import {ParentService} from "./parents/shared/parent.service";
import { RegisterComponent } from './authentication/register/register.component';
import { LoginComponent } from './authentication/login/login.component';
import { LogoutComponent } from './authentication/logout/logout.component';
import { FilterDestinationsComponent } from './parents/filter-destinations/filter-destinations.component';

@NgModule({
  declarations: [
    AppComponent,
    ParentsComponent,
    ParentListComponent,
    ParentAddComponent,
    ParentDeleteComponent,
    ParentUpdateComponent,
    RegisterComponent,
    LoginComponent,
    LogoutComponent,
    FilterDestinationsComponent
  ],
  imports: [
    BrowserModule,
    BrowserAnimationsModule,
    HttpClientModule,
    AppRoutingModule,
    RouterModule,
    ReactiveFormsModule,
    MatInputModule,
    MatButtonModule,
    MatSelectModule,
    MatCheckboxModule,
    MatChipsModule,
    MatTableModule,
    MatSortModule,
    MatPaginatorModule,
    MatMenuModule,
    MatIconModule,
    FormsModule,
    MatToolbarModule,
  ],
  providers: [ParentService],
  bootstrap: [AppComponent]
})
export class AppModule { }
